/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RDP.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 18:49:15 by soutchak          #+#    #+#             */
/*   Updated: 2024/05/05 16:14:34 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"
#include "../../inc/memory.h"

t_tree	*parse_exec(t_token **tokens)
{
	t_tree	*exec;
	t_exec	*node;

	node = init_exec();
	exec = parse_cmd_and_redirs(tokens, node);
	node->argv = ft_realloc(node->argv, sizeof(char *) * (node->argc), \
							sizeof(char *) * (node->argc + 1));
	if (!node->argv)
		return (NULL);
	node->argv[node->argc] = NULL;
	return (exec);
}

t_tree	*parse_redir(t_token **tokens, t_tree *child)
{
	t_tree	*redir;
	t_redir	*last_redir;
	t_etype	type;
	char	*s;

	if (!(*tokens) || !((*tokens)->type & REDIR))
		return (NULL);
	type = (*tokens)->type;
	(*tokens) = (*tokens)->next;
	if (!(*tokens) || !((*tokens)->type & STRING))
		return (NULL);
	s = ft_strndup((*tokens)->location.start, (*tokens)->location.len);
	(*tokens) = (*tokens)->next;
	last_redir = get_last_redir(child);
	if (last_redir)
	{
		redir = redir_node(type, last_redir->child, s);
		last_redir->child = redir;
		redir = child;
	}
	else
		redir = redir_node(type, child, s);
	return (redir);
}

t_tree	*parse_block(t_token **tokens)
{
	t_tree	*block;
	t_tree	*child;

	if (!(*tokens) || (*tokens)->type != LPAR)
		return (NULL);
	(*tokens) = (*tokens)->next;
	child = parse_pipe(tokens);
	if (!child)
		return (NULL);
	if ((*tokens) && ((*tokens)->type & CTRL))
	{
		child = parse_sequence_tail(tokens, child);
		if (!child)
			return (NULL);
	}
	if (!(*tokens) || (*tokens)->type != RPAR)
		return (NULL);
	(*tokens) = (*tokens)->next;
	block = block_node(child);
	while ((*tokens) && (*tokens)->type & REDIR)
		block = parse_redir(tokens, block);
	return (block);
}

t_tree	*parse_pipe(t_token **tokens)
{
	t_pipe	*pipe;
	t_tree	*exec;

	pipe = (t_pipe *)pipe_node();
	if (!pipe)
		return (NULL);
	exec = NULL;
	while ((*tokens))
	{
		if ((*tokens)->type == LPAR)
			exec = parse_block(tokens);
		else
			exec = parse_exec(tokens);
		if (!exec)
			return (NULL);
		pipe = (t_pipe *)pipe_add_node((t_tree *)pipe, exec);
		if ((*tokens) && (*tokens)->type == PIPE)
			(*tokens) = (*tokens)->next;
		else
			break ;
	}
	if (pipe->nb_pipes <= 1)
		return (ft_free((void *)pipe, PARSER), (t_tree *)exec);
	return ((t_tree *)pipe);
}

t_tree	*parse_sequence(t_token **tokens)
{
	t_tree	*left;

	left = parse_pipe(tokens);
	if (!left)
		return (NULL);
	return (parse_sequence_tail(tokens, left));
}
