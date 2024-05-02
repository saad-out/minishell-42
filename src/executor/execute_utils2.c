/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 23:05:53 by soutchak          #+#    #+#             */
/*   Updated: 2024/05/02 23:06:19 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/executor.h"
#include "../../inc/globals.h"

void	child(t_exec *exec)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	execve(exec->argv[0], exec->argv, rebuild_env_to_char(*(exec->env)));
	error(exec->argv[0], NULL);
	set_exit_status(127);
	exit(get_exit_status());
}

int	parent(t_exec *exec)
{
	int	status_;

	wait(&status_);
	if (WIFEXITED(status_))
		status_ = WEXITSTATUS(status_);
	else if (WIFSIGNALED(status_))
		status_ = WTERMSIG(status_) + 128;
	set_under(exec->argv, exec->argc);
	set_exit_status(status_);
	ft_init_signals();
	return (status_);
}
