/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 23:02:37 by soutchak          #+#    #+#             */
/*   Updated: 2024/05/11 15:27:19 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/executor.h"
#include "../../inc/expander.h"
#include "../../inc/globals.h"
#include "../../inc/memory.h"

int	run_ctrl(t_tree *tree)
{
	t_and_or	*and_or;
	int			status_;

	and_or = (t_and_or *)tree;
	status_ = 0;
	if (and_or->type == AND)
	{
		status_ = get_status(and_or->left);
		if (status_ == EXIT_SUCCESS)
			status_ = get_status(and_or->right);
	}
	else if (and_or->type == OR)
	{
		status_ = get_status(and_or->left);
		if (status_ != EXIT_SUCCESS)
			status_ = get_status(and_or->right);
	}
	set_exit_status(status_);
	return (status_);
}

int	run_block(t_tree *tree)
{
	t_block	*block;
	int		status_;

	block = (t_block *)tree;
	status_ = 0;
	signal(SIGINT, interrput_handler_3);
	signal(SIGQUIT, interrput_handler_3);
	if (fork() == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		status_ = get_status(block->child);
		set_exit_status(status_);
		ft_free_heap();
		exit(status_);
	}
	wait(&status_);
	if (WIFEXITED(status_))
		status_ = WEXITSTATUS(status_);
	else
		status_ = EXIT_FAILURE;
	set_exit_status(status_);
	ft_init_signals();
	return (status_);
}

int	run_pipe(t_tree *tree)
{
	t_pipe	*pipe_node;
	pid_t	last_pid;
	int		status_;
	size_t	i;

	set_exit_status(0);
	pipe_node = (t_pipe *)tree;
	status_ = 0;
	last_pid = lunch_pipes(pipe_node);
	waitpid(last_pid, &status_, 0);
	if (WIFEXITED(status_))
		status_ = WEXITSTATUS(status_);
	else
		status_ = EXIT_FAILURE;
	i = 0;
	while (i++ < pipe_node->nb_pipes - 1)
		wait(NULL);
	set_exit_status(status_);
	ft_init_signals();
	return (status_);
}

int	run_redir(t_tree *tree)
{
	t_redir	*redir;
	int		fd;
	int		copy_fd;
	int		status_;

	redir = (t_redir *)tree;
	expander((t_tree *)redir);
	if (!redir->file)
		return (set_exit_status(1), 1);
	fd = open(redir->file, redir->flags, 0644);
	if (fd == -1)
	{
		error(redir->file, NULL);
		return (set_exit_status(1), 1);
	}
	copy_fd = dup(redir->fd);
	dup2(fd, redir->fd);
	status_ = get_status(redir->child);
	set_exit_status(status_);
	close(fd);
	dup2(copy_fd, redir->fd);
	close(copy_fd);
	if (redir->type == HEREDOC)
		unlink(redir->file);
	return (status_);
}

int	run_cmd(t_tree *tree)
{
	t_exec	*exec;
	int		status_;
	int		(*builtin)(t_exec *exec);

	exec = (t_exec *)tree;
	if (exec->argc == 0)
		return (set_exit_status(0), 0);
	status_ = 0;
	exec->env = get_env_list();
	expander((t_tree *)exec);
	if (exec->argc == 0)
		return (set_exit_status(0), 0);
	builtin = is_builtin(exec->argv[0]);
	if (builtin)
		return (set_exit_status(builtin(exec)), get_exit_status());
	status_ = check_cmd(exec);
	if (status_ != 0)
		return (status_);
	signal(SIGINT, interrput_handler_2);
	signal(SIGQUIT, interrput_handler_2);
	if (fork() == 0)
		child(exec);
	return (parent(exec));
}
