/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 18:53:10 by klakbuic          #+#    #+#             */
/*   Updated: 2024/04/23 07:39:23 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/common.h"

int	ft_env(t_exec *cmd)
{
	t_env *head;

	if (cmd->argc > 1)
	{
		ft_putendl_fd("Too many args", STDERR_FILENO);
		return (1);
	}
	head = *(cmd->env);
	while (head)
	{
		if (head->masked == false && (head->visibility & (ENVE | BOTH)))
			printf("%s=%s\n", head->key, head->value);
		head = head->next;
	}
	return (EXIT_SUCCESS);
}