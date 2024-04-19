/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 23:35:30 by soutchak          #+#    #+#             */
/*   Updated: 2024/04/19 15:46:50 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

t_tree	*parse_exec(t_token **tokens)
{
	t_tree	*exec;
	t_exec	*node;
	t_token	*tmp;

	// printf("parse_exec\n");
	node = malloc(sizeof(t_exec));
	if (!node)
		return (NULL);
	node->type = EXEC;
	node->argv = NULL;
	node->argc = 0;
	node->env = NULL;
	tmp = *tokens;
	exec = (t_tree *)node;
	while (tmp)
	{
		if (tmp->type & STRING)
		{
			node->argv = realloc(node->argv, sizeof(char *) * (node->argc + 1));
			if (!node->argv)
				return (NULL);
			node->argv[node->argc] = strndup(tmp->location.start, tmp->location.len); // TODO: do not use library functions
			node->argc++;
			tmp = tmp->next;
		}
		else if (tmp->type  & REDIR)
		{
			exec = parse_redir(&tmp, exec);
			if (!exec)
				return (NULL);
		}
		else
			break ;
	}
	node->argv = realloc(node->argv, sizeof(char *) * (node->argc + 1));
	if (!node->argv)
		return (NULL);
	node->argv[node->argc] = NULL;
	*tokens = tmp;
	return (exec);
}

t_tree	*parse_redir(t_token **tokens, t_tree *child)
{
	t_tree	*redir;
	t_redir	*last_redir;
	t_etype	type;
	char	*s;

	// printf("parse_redir\n");
	if (!(*tokens) || !((*tokens)->type & REDIR))
		return (NULL);
	type = (*tokens)->type;
	(*tokens) = (*tokens)->next;
	if (!(*tokens) || !((*tokens)->type & STRING))
		return (NULL);
	s = strndup((*tokens)->location.start, (*tokens)->location.len); // TODO: do not use library functions
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

	// printf("parse_block\n");
	if ((*tokens)->type != LPAR)
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
	if ((*tokens)->type != RPAR)
		return (NULL);
	(*tokens) = (*tokens)->next;
	block = block_node(child);
	if (!block)
		return (NULL);
	// parse remaining redirs
	while ((*tokens) && (*tokens)->type & REDIR)
	{
		block = parse_redir(tokens, block);
		if (!block)
			return (NULL);
	}
	return (block);
}

t_tree	*parse_pipe(t_token **tokens)
{
	t_pipe	*pipe;
	t_tree	*exec;

	// printf("parse_pipe\n");
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
		return (free(pipe), (t_tree *)exec);
	return ((t_tree *)pipe);
}

t_tree	*parse_sequence_tail(t_token **tokens, t_tree *left)
{
	t_tree	*right;
	t_etype	type;

	// printf("parse_sequence_tail\n");
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

t_tree	*parse_sequence(t_token **tokens)
{
	t_tree	*left;
	t_etype	type;

	// printf("parse_sequence\n");
	left = parse_pipe(tokens);
	if (!left)
		return (NULL);
	return (parse_sequence_tail(tokens, left));
}

void	parser(t_tree **tree, t_token *tokens)
{
	*tree = parse_sequence(&tokens);
	if (!*tree)
		printf("parse error\n");
}
