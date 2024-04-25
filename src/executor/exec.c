/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 23:43:10 by soutchak          #+#    #+#             */
/*   Updated: 2024/04/25 16:21:21 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/executor.h"

void	free_tab(char **tab)
{
	for (size_t i = 0; tab[i]; i++)
		free(tab[i]);
	free(tab);
}

char	*get_cmd_path(char *cmd)
{
	char	*path_var;
	char	**paths;
	char	*full_path;
	char	*tmp;

	if (ft_strcmp(cmd, "") == 0)
	{
		ft_putstr_fd("outlaakSH: \"\"", STDERR_FILENO);
		// ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putendl_fd(": command not found", STDERR_FILENO);
		return (NULL);
	}
	path_var = getenv("PATH");
	if (!path_var)
	{
		printf("outlaakSH: %s: command not found\n", cmd); // cmd memory leak
		return (NULL); //TODO: handle this case as error
	}
	paths = ft_split(path_var, ':');
	if (!paths)
		return (NULL); //TODO: handle this case as error
	for (size_t i = 0; paths[i]; i++)
	{
		// TODO: handle failure of ft_strjoin
		tmp = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(tmp, cmd);
		if (access(full_path, F_OK) == 0)
			return (free_tab(paths), free(tmp), full_path);
		free(full_path);
		free(tmp);
	}
	// free(path_var);
	free_tab(paths);
	//printf("outlaakSH: %s: command not found\n", cmd); // cmd memory leak
	ft_putstr_fd("outlaakSH: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putendl_fd(": command not found", STDERR_FILENO);
	return (NULL);
}
