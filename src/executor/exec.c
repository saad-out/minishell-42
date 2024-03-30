/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 23:43:10 by soutchak          #+#    #+#             */
/*   Updated: 2024/03/30 07:01:40 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/executor.h"

void	free_tab(char **tab)
{
	for (size_t i = 0; tab[i]; i++)
		free(tab[i]);
	free(tab);
}

char *get_env_var(const char *var)
{
	for (size_t i = 0; env_[i]; i++)
	{
		if (ft_strncmp(env_[i], var, ft_strlen(var)) == 0)
			return (ft_strchr(env_[i], '=') + 1);
	}
	return (NULL);
}

char	*get_cmd_path(char *cmd)
{
	char	*path_var;
	char	**paths;
	char	*full_path;
	char	*tmp;

	path_var = get_env_var("PATH");
	if (!path_var)
		return (NULL); //TODO: handle this case as error
	// printf("PATH: %s\n", path_var);
	paths = ft_split(path_var, ':');
	if (!paths)
		return (NULL); //TODO: handle this case as error
	for (size_t i = 0; paths[i]; i++)
	{
		// TODO: handle failure of ft_strjoin
		// printf("lets test: %s\n", paths[i]);
		tmp = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(tmp, cmd);
		if (access(full_path, F_OK) == 0)
			return (free_tab(paths), free(tmp), full_path);
			// return (free(path_var), free_tab(paths), free(tmp), full_path);
		free(full_path);
		free(tmp);
	}
	// free(path_var);
	free_tab(paths);
	return (NULL);
}
