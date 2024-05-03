/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 17:34:18 by soutchak          #+#    #+#             */
/*   Updated: 2024/05/02 18:29:33 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/globals.h"
#include "../inc/memory.h"
#include "../inc/minishell.h"

// t_env	*env_ = NULL;
// int		status = 0;

int	main(int ac, char **av, char **env)
{
	t_env	**env_;

	env_ = NULL;
	env_ = get_env_list();
	*env_ = build_env(env);
	// env_ = build_env(env);
	minishell();
	ft_free_context(GENERAL);
	return (0);
}
