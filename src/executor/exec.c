/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 23:43:10 by soutchak          #+#    #+#             */
/*   Updated: 2024/05/02 23:55:34 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/executor.h"
#include "../../inc/globals.h"

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
		return (NULL);
	path_var = get_env_value(*get_env_list(),"PATH");
	if (!path_var)
		return (NULL); //TODO: handle this case as error
	paths = ft_split(path_var, ':');
	if (!paths)
		return (NULL); //TODO: handle this case as error
	for (size_t i = 0; paths[i]; i++)
	{
		tmp = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(tmp, cmd);
		if (access(full_path, F_OK) == 0)
			return (free_tab(paths), free(tmp), full_path);
		free(full_path);
		free(tmp);
	}
	free_tab(paths);
	return (NULL);
}

static int	last_char(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (str[i - 1]);
}

int	check_leading_paths(char *full_path, char **paths, char **joined, int *i)	
{
	struct stat	info;

	while (paths[(*i) + 1])
	{
		if ((*i) > 0 || full_path[0] == '/')
			(*joined) = ft_strjoin((*joined), "/");
		(*joined) = ft_strjoin((*joined), paths[*i]);
		if (access((*joined), F_OK) == -1)
			return (error(full_path, "No such file or directory"), 127);
		stat((*joined), &info);
		if (!S_ISDIR(info.st_mode))
			return (error(full_path, "Not a directory"), 126);
		(*i)++;
	}
	return (0);
}

int	check_last_path(char *full_path, char **paths, char **joined, int i)
{
	struct stat	info;

	if (last_char(full_path) == '/')
	{
		(*joined) = ft_strjoin((*joined), "/");
		(*joined) = ft_strjoin((*joined), paths[i]);
		if (access((*joined), F_OK) == -1)
			return (error(full_path, "No such file or directory"), 127);
		stat((*joined), &info);
		if (!S_ISDIR(info.st_mode))
			return (error(full_path, "Not a directory"), 126);
	}
	return (0);
}

int	check_paths(char *full_path)
{
	char	**paths;
	int		max_i;
	int		i;
	char	*joined;
	int		status_;
	

	if (full_path[0] == '/' && full_path[1] == '\0')
		return (0);
	paths = ft_split(full_path, '/');
	joined = NULL;
	i = 0;
	status_ = check_leading_paths(full_path, paths, &joined, &i);
	if (status_ != 0)
		return (status_);
	return (check_last_path(full_path, paths, &joined, i));
}
