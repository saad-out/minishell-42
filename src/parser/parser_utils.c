/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 06:10:57 by soutchak          #+#    #+#             */
/*   Updated: 2024/05/02 19:15:34 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"
#include "../../inc/memory.h"

t_exec	*init_exec(void)
{
	t_exec	*node;

	node = ft_malloc(sizeof(t_exec), PARSER);
	node->type = EXEC;
	node->argv = NULL;
	node->argc = 0;
	node->env = NULL;
	return (node);
}

void	parse_str(t_token *tmp, t_exec *node)
{
	node->argv = ft_realloc(node->argv, sizeof(char *) * (node->argc), \
							sizeof(char *) * (node->argc + 1));
	node->argv[node->argc] = ft_strndup(tmp->location.start, tmp->location.len);
	node->argc++;
}

t_tree	*parse_cmd_and_redirs(t_token **tokens, t_exec *node)
{
	t_token	*tmp;
	t_tree	*exec;

	exec = (t_tree *)node;
	tmp = *tokens;
	while (tmp)
	{
		if (tmp->type & STRING)
		{
			parse_str(tmp, node);
			tmp = tmp->next;
		}
		else if (tmp->type & REDIR)
		{
			exec = parse_redir(&tmp, exec);
			if (!exec)
				return (NULL);
		}
		else
			break ;
	}
	*tokens = tmp;
	return (exec);
}

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
	expand = true;
	filename = read_heardoc(s, &expand);
	node->expand = expand;
	if (!filename)
		return (NULL);
	return (node->file = filename, node->file);
}
