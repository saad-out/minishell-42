/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 17:34:18 by soutchak          #+#    #+#             */
/*   Updated: 2024/05/03 21:35:31 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/globals.h"
#include "../inc/memory.h"
#include "../inc/minishell.h"

int	main(int ac, char **av, char **env)
{
	t_env	**env_;

	(void)ac;
	(void)av;
	env_ = get_env_list();
	*env_ = build_env(env);
	minishell();
	ft_free_context(GENERAL);
	return (0);
}
