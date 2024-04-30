/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 23:43:10 by soutchak          #+#    #+#             */
/*   Updated: 2024/04/30 22:00:27 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/executor.h"
#include "../../inc/globals.h"

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
	// status = status_;
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
	if (fork() == 0) // TODO: handle fork failure
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		status_ = get_status(block->child);
		// status = status_;
		set_exit_status(status_);
		exit(status_);
	}
	wait(&status_);
	if (WIFEXITED(status_))
		status_ = WEXITSTATUS(status_);
	else
		status_ = EXIT_FAILURE;
	// status = status_;
	set_exit_status(status_);
	ft_init_signals();
	return (status_);
}

int	run_pipe(t_tree *tree)
{
	t_pipe *pipe_node;
	pid_t	last_pid;
	int		input;
	int		status_;
	int		filedes[2];
	
	pipe_node = (t_pipe *)tree;
	status_ = 0;
	input = 0;
	signal(SIGINT, interrput_handler_3);
	signal(SIGQUIT, interrput_handler_3);
	for (size_t i = 0; i < pipe_node->nb_pipes - 1; i++)
	{
		if (pipe(filedes) == -1)
		{
			perror("pipe");
			exit(1); // TODO: free memory & kill all running processes
		}
		spawn_process(input, filedes[1], pipe_node->nodes[i]);
		close(filedes[1]);
		input = filedes[0];
	}
	last_pid = spawn_process(input, 1, pipe_node->nodes[pipe_node->nb_pipes - 1]);
	waitpid(last_pid, &status_, 0);
	if (WIFEXITED(status_))
		status_ = WEXITSTATUS(status_);
	else
		status_ = EXIT_FAILURE;
	for (size_t i = 0; i < pipe_node->nb_pipes - 1; i++)
		wait(NULL);
	// status = status_;
	set_exit_status(status_);
	ft_init_signals();
	return (status_);
}

int	run_redir(t_tree *tree)
{
	t_redir *redir;
	int		fd;
	int		copy_fd;
	int		status_;

	redir = (t_redir *)tree;
	expander((t_tree *)redir);
	if (!redir->file)
		return (set_exit_status(1), 1);
		// return (status = 1, 1);
	copy_fd = dup(redir->fd);
	close(redir->fd); // TODO: handle system call failure
	// TODO: here we need to check file type (if dir report Is a directory error)
	if ((fd = open(redir->file, redir->flags, 0644)) == -1)
	{
		perror("===>> open");
		ft_putendl_fd("minishell: open: No such file or directory kk", 2);
		dup2(copy_fd, redir->fd);
		// status = 1;
		set_exit_status(1);
		return (EXIT_FAILURE);
	}
	status_ = get_status(redir->child);
	// status = status_;
	set_exit_status(status_);
	close(fd);
	dup2(copy_fd, redir->fd);
	if (redir->type == HEREDOC)
		unlink(redir->file); // TODO: handle system call failure
	return (status_);
}

int	run_cmd(t_tree *tree)
{
	t_exec	*exec;
	int		status_;
	int (*builtin)(t_exec *exec);
	struct stat info;

	exec = (t_exec *)tree;
	if (exec->argc == 0)
		return (EXIT_SUCCESS);
	status_ = 0;
	// exec->env = &env_;
	exec->env = get_env_list();
	expander((t_tree *)exec);
	if (exec->argc == 0)
		return (set_exit_status(0), 0);
		// return (status = 0, 0);
	// for (int i = 0; i < exec->argc; i++)
	// 	printf("===> argv[%d]: %s\n", i, exec->argv[i]);
	builtin = is_builtin(exec->argv[0]);
	if (builtin)
		return (set_exit_status(builtin(exec)), get_exit_status());
		// return (status = builtin(exec), status);
	if (exec->argv[0][0] != '/' && exec->argv[0][0] != '.')
		exec->argv[0] = get_cmd_path(exec->argv[0]);
	else
	{
		if (access(exec->argv[0], F_OK) == -1)
		{
			ft_putendl_fd("No such file or directory", STDERR_FILENO);
			return (set_exit_status(127), 127);
			// return (status = 127, 127);
		}
		if (stat(exec->argv[0], &info) == -1)
		{
			ft_putendl_fd("stat() error", STDERR_FILENO);
			return (1);
		}
		if (S_ISDIR(info.st_mode))
		{
			ft_putendl_fd("Is a directory", STDERR_FILENO);
			return (set_exit_status(126), 126);
			// return (status = 126, 126);
		}
		if (access(exec->argv[0], R_OK | X_OK) == -1)
		{
			ft_putendl_fd("Permission denied", STDERR_FILENO);
			return (set_exit_status(126), 126);
			// return (status = 126, 126);
		}
	}
	if (!exec->argv[0])
		return (set_exit_status(127), 127);
		// return (status = 127, 127);

	// signal(SIGINT, SIG_IGN);
	signal(SIGINT, interrput_handler_2);
	signal(SIGQUIT, interrput_handler_2);
	if (fork() == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		// execve(exec->argv[0], exec->argv, NULL);
		execve(exec->argv[0], exec->argv, rebuild_env_to_char(*(exec->env)));
		fprintf(stderr, "minishell: %s: %s\n", exec->argv[0], strerror(errno)); // print on stderr
		// status = 127;
		set_exit_status(127);
		exit(get_exit_status()); //TODO: check if this is the right exit status & free memory
	}
	wait(&status_);
	if (WIFEXITED(status_))
		status_ = WEXITSTATUS(status_);
	else if (WIFSIGNALED(status_))
		status_ = WTERMSIG(status_) + 128;
	// status = status_;
	set_under(exec->argv, exec->argc);
	set_exit_status(status_);
	ft_init_signals();
	return (status_);
}

int	get_status(t_tree *tree)
{
	if (tree->type & CTRL)
		return (run_ctrl(tree));
	else if (tree->type & REDIR)
		return (run_redir(tree));
	else if (tree->type == BLOCK)
		return (run_block(tree));
	else if (tree->type == PIPE)
		return (run_pipe(tree));
	else if (tree->type == EXEC)
		return (run_cmd(tree));
	return (EXIT_FAILURE);
}

void	executor(t_tree *tree)
{
	if (!tree)
		return ;
	// status = get_status(tree);
	set_exit_status(get_status(tree));
}
