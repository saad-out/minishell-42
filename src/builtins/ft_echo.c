/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 09:55:49 by klakbuic          #+#    #+#             */
/*   Updated: 2024/04/19 18:38:42 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/common.h"

static int	check_args(char **argv)
{
	int i;

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
	int i;
	int status;

    // puts("ana f echo");
	status = 0;
	i = check_args(cmd->argv);
	while (i < cmd->argc)
	{
		status = printf("%s", cmd->argv[i]);
		if (status < 0)
			return (1);
		i++;
        if (i < cmd->argc)
            printf(" ");
	}
	if (check_args(cmd->argv) == 1)
		printf("\n");
	return (0);
}