/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:47:57 by klakbuic          #+#    #+#             */
/*   Updated: 2024/04/19 19:07:33 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/common.h"

int	ft_pwd(t_exec *cmd)
{
	char *cwd = NULL;

	if (cmd->argc != 1)
		return (ft_putendl_fd(MANY_ARGS_ERROR, STDERR_FILENO), 1);
	if ((cwd = getcwd(NULL, 1)) != NULL)
		printf("%s\n", cwd);
	else
	{
		perror("getcwd() error");
		//free(cwd);
		return (1);
	}
	free(cwd);
	return (0);
}