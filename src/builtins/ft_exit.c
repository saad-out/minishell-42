/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 16:59:33 by klakbuic          #+#    #+#             */
/*   Updated: 2024/04/20 18:40:47 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/common.h"

static int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || \
			c == '\v' || c == '\f' || c == '\r');
}

static bool	is_valid_numeric(char *arg)
{
	int	i;
	int	j;

	i = 0;
	while (ft_isspace(arg[i]))
		i++;
	if (arg[i] == '+' || arg[i] == '-')
		i++;
	j = 0;
	while (ft_isdigit(arg[i + j]))
		j++;
	if (j > MAX_STATUS_LEN)
		return (false);
	i += j;
	while (ft_isspace(arg[i]))
		i++;
	if (arg[i] != '\0')
		return (false);
	return (true);
}

int	ft_exit(t_exec *exec)
{
	ft_putendl_fd("exit", STDIN_FILENO);
	if (exec->argc == 1)
	{
		// TODO: freeiage;
		exit(0);
	}
	if (!is_valid_numeric(exec->argv[1]))
	{
		ft_putendl_fd("numeric argument required", STDERR_FILENO);
		// TODO: freeiage;
		exit(255);
	}
	if (exec->argc > 2)
	{
		ft_putendl_fd("Too many arguments", STDERR_FILENO);
		return (1);
	}
	exit((int)((unsigned char)ft_atoi(exec->argv[1])));
}