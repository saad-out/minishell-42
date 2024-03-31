/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 06:10:57 by soutchak          #+#    #+#             */
/*   Updated: 2024/03/31 06:21:04 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

t_redir	*get_last_redir(t_tree *tree)
{
	if (!tree || !(tree->type & REDIR))
		return (NULL);
	if (tree->type & REDIR && !(((t_redir *)tree)->child->type & REDIR))
		return ((t_redir *)tree);
	return (get_last_redir(((t_redir *)tree)->child));
}