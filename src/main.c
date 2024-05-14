/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 17:34:18 by soutchak          #+#    #+#             */
/*   Updated: 2024/05/07 18:55:42 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/globals.h"
#include "../inc/memory.h"
#include "../inc/minishell.h"

static void	init_terminal(void)
{
	struct termios	old_term;
	struct termios	new_term;

	if (!isatty(STDIN_FILENO))
		return ;
	tcgetattr(STDIN_FILENO, &old_term);
	new_term = old_term;
	new_term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &new_term);
}

int	main(int ac, char **av, char **env)
{
	t_env	**env_;

	(void)ac;
	(void)av;
	init_terminal();
	env_ = get_env_list();
	*env_ = build_env(env);
	minishell();
	init_terminal();
	ft_free_context(GENERAL);
	return (0);
}
