/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 23:43:10 by soutchak          #+#    #+#             */
/*   Updated: 2024/03/30 05:16:20 by soutchak         ###   ########.fr       */
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
			// exec->argv[0] = get_cmd_path(exec->argv[0]);
			execve(exec->argv[0], exec->argv, NULL);
			printf("minishell: %s: %s\n", exec->argv[0], strerror(errno));
			exit(1); //TODO: check if this is the right exit status & free memory
		}
		wait(NULL);
		// printf("==>waited on exec\n");
		return ;
		// exit(0); //TODO: check if this is the right exit status & free memory
	}
	else if (tree->type == PIPE)
	{
		t_pipe *pipe_node = (t_pipe *)tree;
		int		input = 0;
		for (size_t i = 0; i < pipe_node->nb_pipes - 1; i++)
		{
			int		filedes[2];
			printf("===> pipe between %zu and %zu\n", i, i + 1);
			if (pipe(filedes) == -1)
			{
				perror("pipe");
				exit(1); // TODO: free memory & kill all running processes
			}
			spawn_process(input, filedes[1], pipe_node->nodes[i]);
			close(filedes[1]);
			input = filedes[0];
		}
		spawn_process(input, 1, pipe_node->nodes[pipe_node->nb_pipes - 1]);
		for (size_t i = 0; i < pipe_node->nb_pipes; i++)
			wait(NULL);
		printf("==>waited on pipe\n");
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
