/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 10:33:09 by klakbuic          #+#    #+#             */
/*   Updated: 2024/05/04 02:17:17 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/common.h"
#include "../../inc/globals.h"

void	interrput_handler(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	set_exit_status(1);
}

void	interrput_handler_2(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", STDOUT_FILENO);
	set_exit_status(1);
}

void	interrput_handler_3(int sig)
{
	(void)sig;
	set_exit_status(1);
}

void	ft_init_signals(void)
{
	sig_t	error;

	error = signal(SIGINT, interrput_handler);
	if (error == SIG_ERR)
		ft_putendl_fd("signal() error", STDERR_FILENO);
	error = signal(SIGQUIT, SIG_IGN);
	if (error == SIG_ERR)
		ft_putendl_fd("signal() error", STDERR_FILENO);
}
