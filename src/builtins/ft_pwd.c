/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:47:57 by klakbuic          #+#    #+#             */
/*   Updated: 2024/04/30 08:25:29 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/executor.h"

int	ft_pwd(t_exec *cmd)
{
	char *cwd = NULL;

	if (cmd->argc != 1)
		return (ft_putendl_fd(MANY_ARGS_ERROR, STDERR_FILENO), 1);
	if ((cwd = getcwd(NULL, 1)) != NULL)
		printf("%s\n", cwd);
	else
		return (print_error_builtins("getcwd syscall failed"));
	free(cwd);
	return (EXIT_SUCCESS);
}