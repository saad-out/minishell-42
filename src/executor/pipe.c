/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 23:43:10 by soutchak          #+#    #+#             */
/*   Updated: 2024/03/30 05:07:42 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/executor.h"

int	spawn_process(int input, int output, t_tree *tree)
{
	if (fork() == 0) // TODO: handle system call failure
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
		executor(tree);
		exit(0);
	}
	return (0);
}
