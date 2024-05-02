/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 09:55:49 by klakbuic          #+#    #+#             */
/*   Updated: 2024/05/02 15:58:13 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/common.h"
#include "../../inc/globals.h"

static int	check_args(char **argv)
{
	int	i;

	if (ft_strcmp(argv[1], "-") == 0)
		return (1);
	i = 0;
	if (argv[1][0] == '-')
	{
		while (argv[1][++i])
		{
			if (argv[1][i] != 'n')
				return (1);
		}
		return (2);
	}
	return (1);
}

int	ft_echo(t_exec *cmd)
{
	int	i;

	if (cmd->argc == 1)
		return (printf("\n"), EXIT_SUCCESS);
	i = check_args(cmd->argv);
	while (i < cmd->argc)
	{
		if (ft_strcmp(cmd->argv[i], "$?") == 0)
		{
			printf("%d", get_exit_status());
			set_exit_status(0);
			i++;
			continue ;
		}
		printf("%s", cmd->argv[i]);
		i++;
		if (i < cmd->argc)
			printf(" ");
	}
	if (check_args(cmd->argv) == 1)
		printf("\n");
	return (EXIT_SUCCESS);
}
