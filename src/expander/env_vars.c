/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 15:41:06 by soutchak          #+#    #+#             */
/*   Updated: 2024/05/03 02:45:06 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/expander.h"
#include "../../inc/globals.h"
#include "../../inc/memory.h"

void	expand_vars(t_tree *node)
{
	if (node->type == EXEC)
		return (expand_exec_vars((t_exec *)node));
	else
		return (expand_redir_vars((t_redir *)node));
}
