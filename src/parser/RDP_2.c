/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RDP_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 18:50:49 by soutchak          #+#    #+#             */
/*   Updated: 2024/05/02 18:51:15 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"
#include "../../inc/memory.h"

t_tree	*parse_sequence_tail(t_token **tokens, t_tree *left)
{
	t_tree	*right;
	t_etype	type;

	if (!(*tokens))
		return (left);
	else if (!((*tokens)->type & CTRL))
		return (NULL);
	type = (*tokens)->type;
	(*tokens) = (*tokens)->next;
	right = parse_pipe(tokens);
	if (!right)
		return (NULL);
	if (!(*tokens) || !((*tokens)->type & CTRL))
		return (and_or_node(type, left, right));
	left = and_or_node(type, left, right);
	return (parse_sequence_tail(tokens, left));
}
