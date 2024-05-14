/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 16:31:41 by soutchak          #+#    #+#             */
/*   Updated: 2024/05/07 19:33:33 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/common.h"
#include "../../inc/globals.h"
#include "../../inc/memory.h"

void	set_shelvl(t_env *new)
{
	int	old_shlvl;

	if (new->value)
	{
		old_shlvl = ft_atoi(new->value);
		if (old_shlvl < 0)
			new->value = ft_itoa(0);
		else if (old_shlvl >= 999)
		{
			ft_putstr_fd("outlaakSH: warning: shell level(1000) ", 2);
			ft_putendl_fd("too high, resetting to 1", 2);
			new->value = ft_itoa(1);
		}
		else
			new->value = ft_itoa(++old_shlvl);
	}
}
