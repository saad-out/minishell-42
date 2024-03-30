/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 23:43:10 by soutchak          #+#    #+#             */
/*   Updated: 2024/03/30 03:18:30 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/executor.h"

void	executor(t_tree *tree)
{
	if (!tree)
		return ;
	if (tree->type == EXEC)
	{
		if (fork() == 0)
		{
			t_exec *exec = (t_exec *)tree;
			execve(exec->argv[0], exec->argv, NULL);
			printf("minishell: %s: %s\n", exec->argv[0], strerror(errno));
		}
		wait(NULL);
	}
	else if (tree->type == PIPE)
	{
		t_pipe *pipe = (t_pipe *)tree;
		for (size_t i = 0; i < pipe->nb_pipes; i++)
		{
			executor(pipe->nodes[i]);
		}
	}
	else if (tree->type == REDIR)
	{
		t_redir *redir = (t_redir *)tree;
		executor(redir->child);
	}
	else if (tree->type == AND || tree->type == OR)
	{
		t_and_or *and_or = (t_and_or *)tree;
		executor(and_or->left);
		executor(and_or->right);
	}
	else if (tree->type == BLOCK)
	{
		t_block *block = (t_block *)tree;
		executor(block->child);
	}
}
