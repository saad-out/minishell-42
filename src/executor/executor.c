/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 23:43:10 by soutchak          #+#    #+#             */
/*   Updated: 2024/05/02 23:05:35 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/executor.h"
#include "../../inc/globals.h"

int	get_status(t_tree *tree)
{
	if (tree->type & CTRL)
		return (run_ctrl(tree));
	else if (tree->type & REDIR)
		return (run_redir(tree));
	else if (tree->type == BLOCK)
		return (run_block(tree));
	else if (tree->type == PIPE)
		return (run_pipe(tree));
	else if (tree->type == EXEC)
		return (run_cmd(tree));
	return (EXIT_FAILURE);
}

void	executor(t_tree *tree)
{
	if (!tree)
		return ;
	set_exit_status(get_status(tree));
}
