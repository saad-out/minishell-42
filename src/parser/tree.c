/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 03:15:28 by soutchak          #+#    #+#             */
/*   Updated: 2024/04/01 02:03:07 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

void    free_tree(t_tree *tree)
{
    t_and_or    *and_or;
    t_pipe      *pipe;
    t_exec      *exec;
    t_block     *block;
    t_redir     *redir;

    if (!tree)
        return ;
    if (tree->type == AND || tree->type == OR)
    {
        and_or = (t_and_or *)tree;
        free_tree(and_or->left);
        free_tree(and_or->right);
    }
    else if (tree->type == PIPE)
    {
        pipe = (t_pipe *)tree;
        for (size_t i = 0; i < pipe->nb_pipes; i++)
            free_tree(pipe->nodes[i]);
        // free(pipe->nodes);
    }
    else if (tree->type == WORD)
    {
        exec = (t_exec *)tree;
        for (int i = 0; i < exec->argc; i++)
            free(exec->argv[i]);
        free(exec->argv);
        // free_env(exec->env);
    }
    else if (tree->type == BLOCK)
    {
        block = (t_block *)tree;
        free_tree(block->child);
    }
    else if (tree->type == REDIR)
    {
        redir = (t_redir *)tree;
        free_tree(redir->child);
    }
    free(tree);
}

void	visit_tree(t_tree *tree, int depth)
{
	if (!tree)
		return ;
	if (tree->type == EXEC)
	{
		t_exec	*node = (t_exec *)tree;
		for (int i = 0; i < depth; i++)
			printf("\t");
		printf("EXEC: ");
		for (int i = 0; i < node->argc; i++)
		{
			// for (int j = 0; j < depth; j++)
			// 	printf("  ");
			printf("%s ", node->argv[i]);
		}
		printf("\n");
	}
	else if (tree->type == REDIR_IN || tree->type == REDIR_OUT || tree->type == APPEND || tree->type == HEREDOC)
	{
		t_redir	*node = (t_redir *)tree;
		for (int i = 0; i < depth; i++)
			printf("\t");
		// printf("REDIR: %s %s\n", token_type_to_str(node->type), node->file);
		printf("%s ==> %s:\n", token_type_to_str(node->type), node->file);
		visit_tree(node->child, depth + 1);
	}
	else if (tree->type == PIPE)
	{
		t_pipe	*node = (t_pipe *)tree;
		for (int i = 0; i < depth; i++)
			printf("\t");
		printf("PIPE: %zu\n", node->nb_pipes);
		for (size_t i = 0; i < node->nb_pipes; i++)
			visit_tree(node->nodes[i], depth + 1);
	}
	else if (tree->type == BLOCK)
	{
		t_block	*node = (t_block *)tree;
		for (int i = 0; i < depth; i++)
			printf("\t");
		printf("BLOCK ():\n");
		visit_tree(node->child, depth + 1);
	}
	else if (tree->type == AND || tree->type == OR)
	{
		t_and_or	*node = (t_and_or *)tree;
		for (int i = 0; i < depth; i++)
			printf("\t");
		// printf("AND_OR: %s\n", token_type_to_str(node->type));
		printf("%s:\n", token_type_to_str(node->type));
		visit_tree(node->left, depth + 1);
		visit_tree(node->right, depth + 1);
	}
}
