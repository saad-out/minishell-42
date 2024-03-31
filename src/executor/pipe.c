/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 23:43:10 by soutchak          #+#    #+#             */
/*   Updated: 2024/03/31 04:49:24 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/executor.h"

pid_t	spawn_process(int input, int output, t_tree *tree)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0) // TODO: handle system call failure
	{
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
		status = get_status(tree);
		exit(status);
	}
	return (pid);
}
