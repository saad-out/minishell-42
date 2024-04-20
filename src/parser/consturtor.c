/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   consturtor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 08:27:27 by saad              #+#    #+#             */
/*   Updated: 2024/04/20 16:17:44 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

t_tree	*and_or_node(t_etype type, t_tree *left, t_tree *right)
{
	t_and_or	*node;

	node = malloc(sizeof(t_and_or));
	if (!node)
		return (NULL);
	if (type != AND && type != OR)
		return (NULL);
	node->type = type;
	node->left = left;
	node->right = right;
	return ((t_tree *)node);
}

t_tree *block_node(t_tree *child)
{
	t_block	*node;

	node = malloc(sizeof(t_block));
	if (!node)
		return (NULL);
	node->child = child;
	node->type = BLOCK;
	return ((t_tree *)node);
}

t_tree	*redir_node(t_etype type, t_tree *child, char *s)
{
	t_redir	*node;

	node = malloc(sizeof(t_redir));
	if (!node)
		return (NULL);
	node->type = type;
	if (!set_filename(node, s, type))
		return (NULL);
	if (type == REDIR_IN || type == HEREDOC)
	{
		node->fd = 0;
		node->flags = O_RDONLY;
	}
	else if (type == REDIR_OUT || type == APPEND)
	{
		node->fd = 1;
		node->flags = O_WRONLY | O_CREAT;
		if (type == APPEND)
			node->flags |= O_APPEND;
		if (type == REDIR_OUT)
			node->flags |= O_TRUNC;
	}
	else
		return (NULL);
	node->child = child;
	return ((t_tree *)node);
}

t_tree	*exec_node(char **args, int argc, char **env)
{
	t_exec	*node;

	node = malloc(sizeof(t_exec));
	if (!node)
		return (NULL);
	node->type = EXEC;
	node->argv = args;
	node->argc = argc;
	// node->env = env;
	return ((t_tree *)node);
}

t_tree	*pipe_node(void)
{
	t_pipe	*node;

	node = malloc(sizeof(t_pipe));
	if (!node)
		return (NULL);
	node->type = PIPE;
	node->nb_pipes = 0;
	return ((t_tree *)node);
}

t_tree	*pipe_add_node(t_tree *pipe, t_tree *node)
{
	t_pipe	*pipe_node;

	if (!pipe || !node)
		return (NULL);
	pipe_node = (t_pipe *)pipe;
	if (pipe_node->nb_pipes >= 10)
		return (NULL);
	pipe_node->nodes[pipe_node->nb_pipes] = node;
	pipe_node->nb_pipes++;
	return (pipe);
}
