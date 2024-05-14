/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 18:53:10 by klakbuic          #+#    #+#             */
/*   Updated: 2024/05/05 15:46:32 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/common.h"

int	ft_env(t_exec *cmd)
{
	t_env	*head;

	set_under(cmd->argv, cmd->argc);
	if (cmd->argc > 1)
	{
		ft_putendl_fd("Too many args", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	head = *(cmd->env);
	while (head)
	{
		if (head->masked == false && (head->visibility & (BOTH | ENVE)))
			printf("%s=%s\n", head->key, head->value);
		head = head->next;
	}
	return (EXIT_SUCCESS);
}
