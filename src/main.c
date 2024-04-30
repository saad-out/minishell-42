/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 17:34:18 by soutchak          #+#    #+#             */
/*   Updated: 2024/04/29 18:48:40 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/globals.h"

// t_env	*env_ = NULL;
// int		status = 0;

int	main(int ac, char **av, char **env)
{
	t_env	**env_ = NULL;

	env_ = get_env_list();
	*env_ = build_env(env);
	// env_ = build_env(env);
	minishell();
	return (0);
}
