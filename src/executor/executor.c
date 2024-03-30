/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 23:43:10 by soutchak          #+#    #+#             */
/*   Updated: 2024/03/30 07:04:12 by soutchak         ###   ########.fr       */
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
			if (exec->argv[0][0] != '/' && exec->argv[0][0] != '.')
				exec->argv[0] = get_cmd_path(exec->argv[0]);
			// printf("==>executing %s\n", exec->argv[0]);
			if (!exec->argv[0])
			{
				printf("command not found\n");
				return ;
			}
			execve(exec->argv[0], exec->argv, NULL);
			printf("minishell: %s: %s\n", exec->argv[0], strerror(errno)); // print on stderr
			exit(1); //TODO: check if this is the right exit status & free memory
		}
		wait(NULL);
		// printf("==>executed succesfully\n");
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
	else if (tree->type & REDIR)
	{
		t_redir *redir = (t_redir *)tree;
		int		fd;
		int		copy_fd = dup(redir->fd);
		close(redir->fd); // TODO: handle system call failure
		if ((fd = open(redir->file, redir->flags, 0644)) == -1)
		{
			perror("open");
			exit(1); // TODO: free memory & kill all running processes
		}
		executor(redir->child);
		close(fd);
		dup2(copy_fd, redir->fd);
	}
	else if (tree->type & CTRL)
	{
		t_and_or *and_or = (t_and_or *)tree;
		executor(and_or->left);
		executor(and_or->right);
	}
	else if (tree->type == BLOCK)
	{
		t_block *block = (t_block *)tree;
		if (fork() == 0) // TODO: handle fork failure
		{
			executor(block->child);
			exit(0); //TODO: check if this is the right exit status & free memory
		}
		wait(NULL);
	}
}
