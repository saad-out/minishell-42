/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 09:53:23 by klakbuic          #+#    #+#             */
/*   Updated: 2024/04/30 12:19:58 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/common.h"
#include "../../inc/executor.h"

static void	change_pwd(t_env *envs, char *old_pwd, char *pwd)
{
	set_env(envs, "OLDPWD", old_pwd);
	set_env(envs, "PWD", pwd);
}

int	ft_cd(t_exec *cmd)
{
	char		*tmp;
	char		*old_pwd;
	struct stat	info;

	old_pwd = getcwd(NULL, 1);
	if (old_pwd == NULL)
		return (print_error_builtins("getcwd() error"));
	if (cmd->argc == EXIT_FAILURE)
	{
		tmp = get_env_value(*(cmd->env), "HOME");
		if (!tmp)
			return (print_error_builtins("cd : HOME not set"));
		if (chdir(tmp) == -1)
			return (EXIT_FAILURE);
	}
	else if (ft_strcmp(cmd->argv[1], "-") == 0)
	{
		tmp = get_env_value(*(cmd->env), "OLDPWD");
		if (!tmp)
			return (print_error_builtins("cd : OLDPWD not set"));
		if (chdir(tmp) == -1)
			return (print_error_builtins("chdir() error"));
		ft_putendl_fd(tmp, STDOUT_FILENO);
	}
	else
	{
		if (access(cmd->argv[1], F_OK) == -1)
			return (print_error_builtins("cd: No such file or directory"));
		if (stat(cmd->argv[1], &info) == -1)
			return (print_error_builtins("stat() error"));
		if (!S_ISDIR(info.st_mode))
			return (print_error_builtins("cd: Not a directory"));
		if (access(cmd->argv[1], R_OK | X_OK) == -1)
			print_error_builtins("Permission denied");
		if (chdir(cmd->argv[1]) == -1)
			return (print_error_builtins("chdir() error"));
		tmp = cmd->argv[1];
	}
	change_pwd(*(cmd->env), old_pwd, tmp);
	return (set_under(cmd->argv, cmd->argc), EXIT_SUCCESS);
}
