/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 10:35:40 by klakbuic          #+#    #+#             */
/*   Updated: 2024/04/24 06:45:33 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/common.h"

static void	ft_swap(t_env *a, t_env *b)
{
	t_env	tmp;

	tmp.key = a->key;
	tmp.value = a->value;
	tmp.visibility = a->visibility;
	tmp.masked = a->masked;
	a->key = b->key;
	a->value = b->value;
	a->visibility = b->visibility;
	a->masked = b->masked;
	b->key = tmp.key;
	b->value = tmp.value;
	b->visibility = tmp.visibility;
	b->masked = tmp.masked;
}

void	sort_envs(t_env **envs)
{
	int		swapped;
	t_env	*env;

	while (true)
	{
		env = *envs;
		swapped = 0;
		while (env->next)
		{
			if (strcmp(env->key, env->next->key) > 0)
			{
				ft_swap(env, env->next);
				swapped = 1;
			}
			env = env->next;
		}
		if (swapped == 0)
			break ;
	}
}
