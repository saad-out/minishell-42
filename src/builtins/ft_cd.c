/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 09:53:23 by klakbuic          #+#    #+#             */
/*   Updated: 2024/05/02 15:54:58 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/common.h"
#include "../../inc/executor.h"

static void	change_pwd(t_env *envs, char *old_pwd, char *pwd)
{
	set_env(envs, "OLDPWD", old_pwd);
	set_env(envs, "PWD", pwd);
}

static int	ft_cd_helper(t_exec *cmd)
{
	char	*tmp;

	if (cmd->argc == 1)
	{
		tmp = get_env_value(*(cmd->env), "HOME");
		if (!tmp)
			return (error("cd", "HOME not set"), EXIT_FAILURE);
		if (chdir(tmp) == -1)
			return (EXIT_FAILURE);
	}
	else if (ft_strcmp(cmd->argv[1], "-") == 0)
	{
		tmp = get_env_value(*(cmd->env), "OLDPWD");
		if (!tmp)
			return (error("cd", "OLDPWD not set"), EXIT_FAILURE);
		tmp = ft_strdup(tmp);
		if (chdir(tmp) == -1)
			return (error("cd", NULL), EXIT_FAILURE);
		ft_putendl_fd(tmp, STDOUT_FILENO);
	}
	return (EXIT_SUCCESS);
}

int	ft_cd(t_exec *cmd)
{
	char		*tmp;
	char		old_pwd[PATH_MAX];
	struct stat	info;

	getcwd(old_pwd, PATH_MAX);
	if (cmd->argc == 1 || ft_strcmp(cmd->argv[1], "-") == 0)
		return (ft_cd_helper(cmd));
	else
	{
		if (access(cmd->argv[1], F_OK) == -1)
			return (error("cd", "No such file or directory"), EXIT_FAILURE);
		if (stat(cmd->argv[1], &info) == -1)
			return (error("cd", NULL), EXIT_FAILURE);
		if (!S_ISDIR(info.st_mode))
			return (error("cd", "Not a directory"), EXIT_FAILURE);
		if (access(cmd->argv[1], R_OK | X_OK) == -1)
			return (error("cd", "Permission denied"), EXIT_FAILURE);
		if (chdir(cmd->argv[1]) == -1)
			return (error("cd", NULL), EXIT_FAILURE);
		tmp = cmd->argv[1];
	}
	change_pwd(*(cmd->env), old_pwd, tmp);
	return (set_under(cmd->argv, cmd->argc), EXIT_SUCCESS);
}
