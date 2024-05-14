/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 23:43:10 by soutchak          #+#    #+#             */
/*   Updated: 2024/05/04 18:50:54 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/executor.h"
#include "../../inc/globals.h"
#include "../../inc/memory.h"

static void	child_pipe(t_tree *tree, int input, int output, int new_input)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (new_input != 0)
		close(new_input);
	if (input != 0)
	{
		dup2(input, STDIN_FILENO);
		close(input);
	}
	if (output != 1)
	{
		dup2(output, STDOUT_FILENO);
		close(output);
	}
	set_exit_status(get_status(tree));
	ft_free_heap();
	exit(get_exit_status());
}

pid_t	spawn_process(int input, int filedes[2], t_tree *tree)
{
	pid_t	pid;
	int		output;
	int		new_input;

	output = filedes[1];
	new_input = filedes[0];
	pid = fork();
	if (pid == 0)
		child_pipe(tree, input, output, new_input);
	if (input != 0)
		close(input);
	return (pid);
}
