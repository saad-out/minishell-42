/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 23:05:53 by soutchak          #+#    #+#             */
/*   Updated: 2024/05/07 18:52:13 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/executor.h"
#include "../../inc/globals.h"
#include "../../inc/memory.h"

void	child(t_exec *exec)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	execve(exec->argv[0], exec->argv, rebuild_env_to_char(*(exec->env)));
	error(exec->argv[0], NULL);
	set_exit_status(127);
	ft_free_heap();
	exit(get_exit_status());
}

int	parent(t_exec *exec)
{
	int	status_;

	wait(&status_);
	if (WIFEXITED(status_))
		status_ = WEXITSTATUS(status_);
	else if (WIFSIGNALED(status_))
		status_ = WTERMSIG(status_) + 128;
	set_under(exec->argv, exec->argc);
	set_exit_status(status_);
	ft_init_signals();
	return (status_);
}

void	free_tab(char **tabi)
{
	size_t	i;

	i = 0;
	while (tabi[i])
		ft_free(tabi[i++], GENERAL);
	ft_free(tabi, GENERAL);
}

char	*get_cmd_path(char *cmd)
{
	char	*path_var;
	char	**paths;
	char	*full_path;
	char	*tmp;
	size_t	i;

	if (ft_strcmp(cmd, "") == 0)
		return (NULL);
	path_var = get_env_value(*get_env_list(), "PATH");
	if (!path_var)
		return (NULL);
	paths = ft_split(path_var, ":");
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(tmp, cmd);
		if (access(full_path, F_OK) == 0)
			return (free_tab(paths), ft_free(tmp, GENERAL), full_path);
		ft_free(full_path, GENERAL);
		ft_free(tmp, GENERAL);
		i++;
	}
	return (free_tab(paths), NULL);
}
