/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 16:37:20 by klakbuic          #+#    #+#             */
/*   Updated: 2024/05/02 19:00:22 by klakbuic         ###   ########.fr       */
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
	return (set_under(cmd->argv, cmd->argc), EXIT_SUCCESS);
}
