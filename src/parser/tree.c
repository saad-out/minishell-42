/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 03:15:28 by soutchak          #+#    #+#             */
/*   Updated: 2024/05/03 21:39:09 by soutchak         ###   ########.fr       */
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
