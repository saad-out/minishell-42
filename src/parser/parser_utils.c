/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saad <saad@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 06:10:57 by soutchak          #+#    #+#             */
/*   Updated: 2024/04/27 01:59:53 by saad             ###   ########.fr       */
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

char	*set_filename(t_redir *node, char *s, t_etype type)
{
	char	*filename;
	bool	expand;

	if (type != HEREDOC)
		return (node->file = s, s);
	expand = false;
	filename = read_heardoc(s, &expand);
	node->expand = expand;
	if (!filename)
		return (NULL);
	return (node->file = filename, node->file);
}
