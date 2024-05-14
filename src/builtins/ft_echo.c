/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 09:55:49 by klakbuic          #+#    #+#             */
/*   Updated: 2024/05/13 17:00:52 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/common.h"
#include "../../inc/globals.h"

static int	check_args(char **argv)
{
	int	i;
	int	j;

	if (ft_strcmp(argv[1], "-") == 0)
		return (1);
	i = 1;
	while (argv[i] && argv[i][0] == '-')
	{
		j = 0;
		while (argv[i][++j])
		{
			if (argv[i][j] != 'n')
				return (i);
		}
		i++;
	}
	return (i);
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
