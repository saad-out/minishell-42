/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 09:53:23 by klakbuic          #+#    #+#             */
/*   Updated: 2024/04/20 16:32:43 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/common.h"
#define SIZE 1024

// static void	change_pwd(t_env *envs, const char *old_pwd, const char *pwd)

static void	change_pwd(t_env *envs, char *old_pwd, char *pwd)
{
	set_env(envs, "OLDPWD", old_pwd);
	set_env(envs, "PWD", pwd);
}

int	ft_cd(t_exec *cmd)
{
	char *tmp;
	char *old_pwd;
	char *pwd;
	struct stat info;

	old_pwd = getcwd(NULL, 1);
	if (old_pwd == NULL)
	{
		ft_putendl_fd("getcwd() error", STDERR_FILENO);
		return (1);
	}
	if (cmd->argc == 1)
	{
		tmp = get_env_value(*(cmd->env), "HOME");
		if (!tmp)
		{
			ft_putendl_fd("cd : HOME not set", STDERR_FILENO);
			return (1);
		}
		if (chdir(tmp) == -1)
			return (1);
	}
	else if (ft_strcmp(cmd->argv[1], "-") == 0)
	{
		tmp = get_env_value(*(cmd->env), "OLDPWD");
		if (!tmp)
		{
			ft_putendl_fd("cd : OLDPWD not set", STDERR_FILENO);
			return (1);
		}
		if (chdir(tmp) == -1)
		{
			ft_putendl_fd("chdir() error", STDERR_FILENO);
			return (1);
		}
		ft_putendl_fd(tmp, STDOUT_FILENO);
	}
	else
	{
		if (access(cmd->argv[1], F_OK) == -1)
		{
			ft_putendl_fd("No such file or directory", STDERR_FILENO);
			return (1);
		}
		if (stat(cmd->argv[1], &info) == -1)
		{
			ft_putendl_fd("stat() error", STDERR_FILENO);
			return (1);
		}
		if (!S_ISDIR(info.st_mode))
		{
			ft_putendl_fd("Not a directory", STDERR_FILENO);
			return (1);
		}
		if (access(cmd->argv[1], R_OK | X_OK) == -1)
		{
			ft_putendl_fd("Permission denied", STDERR_FILENO);
			return (1);
		}
		if (chdir(cmd->argv[1]) == -1)
		{
			ft_putendl_fd("chdir() error", STDERR_FILENO);
			return (1);
		}
		tmp = cmd->argv[1];
	}
	change_pwd(*(cmd->env), old_pwd, tmp);
	return (0);
}