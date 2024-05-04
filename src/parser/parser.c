/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 23:35:30 by soutchak          #+#    #+#             */
/*   Updated: 2024/05/03 17:27:47 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"
#include "../../inc/memory.h"

void	parser(t_tree **tree, t_token *tokens)
{
	*tree = parse_sequence(&tokens);
	if (!*tree)
		error("Syntax error", "parser");
}
