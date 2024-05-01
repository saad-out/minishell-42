/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:47:57 by klakbuic          #+#    #+#             */
/*   Updated: 2024/05/01 15:55:19 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/executor.h"

int	ft_pwd(t_exec *cmd)
{
	char cwd[PATH_MAX];

	if (cmd->argc != 1)
		return (ft_putendl_fd(MANY_ARGS_ERROR, STDERR_FILENO), 1);
	getcwd(cwd, PATH_MAX);
	printf("%s\n", cwd);
	return (set_under(cmd->argv, cmd->argc), EXIT_SUCCESS);
}