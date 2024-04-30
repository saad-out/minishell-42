/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 16:37:20 by klakbuic          #+#    #+#             */
/*   Updated: 2024/04/24 06:56:16 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/common.h"

int	ft_unset(t_exec *cmd)
{
	t_env	*tmp;
	int		i;

	i = 1;
	while (i < cmd->argc)
	{
		tmp = get_env(*(cmd)->env, cmd->argv[i]);
		if (tmp)
			tmp->masked = true;
		i++;
	}
	return (EXIT_SUCCESS);
}
