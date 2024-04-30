/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 23:43:10 by soutchak          #+#    #+#             */
/*   Updated: 2024/04/30 19:08:01 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/executor.h"
#include "../../inc/globals.h"

pid_t	spawn_process(int input, int output, t_tree *tree)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0) // TODO: handle system call failure
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
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
		// status = get_status(tree);
		set_exit_status(get_status(tree));
		exit(get_exit_status());
		// exit(status);
	}
	return (pid);
}
