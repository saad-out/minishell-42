/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 23:43:10 by soutchak          #+#    #+#             */
/*   Updated: 2024/05/04 00:38:24 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/executor.h"
#include "../../inc/globals.h"
#include "../../inc/memory.h"

pid_t	spawn_process(int input, int output, t_tree *tree)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
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
		set_exit_status(get_status(tree));
		ft_free_heap();
		exit(get_exit_status());
	}
	return (pid);
}
