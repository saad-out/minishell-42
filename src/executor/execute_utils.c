/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 23:04:51 by soutchak          #+#    #+#             */
/*   Updated: 2024/05/03 18:07:47 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/executor.h"
#include "../../inc/globals.h"
#include "../../inc/memory.h"

pid_t	lunch_pipes(t_pipe *pipe_node)
{
	int		input;
	int		filedes[2];
	size_t	i;

	input = 0;
	signal(SIGINT, interrput_handler_3);
	signal(SIGQUIT, interrput_handler_3);
	i = 0;
	while (i < pipe_node->nb_pipes - 1)
	{
		if (pipe(filedes) == -1)
		{
			error("pipe", NULL);
			exit(1);
		}
		spawn_process(input, filedes[1], pipe_node->nodes[i]);
		close(filedes[1]);
		input = filedes[0];
		i++;
	}
	return (spawn_process(input, 1, pipe_node->nodes[pipe_node->nb_pipes - 1]));
}

int	run_from_path(t_exec *exec)
{
	char	*tmp;

	tmp = get_cmd_path(exec->argv[0]);
	if (!tmp)
	{
		error(exec->argv[0], "command not found");
		set_under(exec->argv, exec->argc);
		return (set_exit_status(127), 127);
	}
	ft_free(exec->argv[0], GENERAL);
	exec->argv[0] = tmp;
	return (0);
}

int	run_exec(t_exec *exec)
{
	int			i;
	struct stat	info;

	i = check_paths(exec->argv[0]);
	if (i != 0)
		return (set_under(exec->argv, exec->argc), set_exit_status(i), i);
	if (access(exec->argv[0], F_OK) == -1)
	{
		error(exec->argv[0], "No such file or directory");
		return (set_nosplt(exec->argv, exec->argc), set_exit_status(127), 127);
	}
	stat(exec->argv[0], &info);
	if (S_ISDIR(info.st_mode))
	{
		error(exec->argv[0], "Is a directory");
		return (set_nosplt(exec->argv, exec->argc), set_exit_status(126), 126);
	}
	if (access(exec->argv[0], R_OK | X_OK) == -1)
	{
		error(exec->argv[0], "Permission denied");
		return (set_nosplt(exec->argv, exec->argc), set_exit_status(126), 126);
	}
	return (0);
}

int	check_cmd(t_exec *exec)
{
	int			status_;
	char		*tmp;
	struct stat	info;

	if (exec->argv[0][0] != '/' && exec->argv[0][0] != '.')
	{
		status_ = run_from_path(exec);
		if (status_ != 0)
			return (status_);
	}
	else
	{
		status_ = run_exec(exec);
		if (status_ != 0)
			return (status_);
	}
	return (0);
}
