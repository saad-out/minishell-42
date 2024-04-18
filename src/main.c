/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 17:34:18 by soutchak          #+#    #+#             */
/*   Updated: 2024/04/18 22:53:49 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_env	*env_ = NULL;
int		status = 0;

int	main(int ac, char **av, char **env)
{
	env_ = build_env(env);
	minishell();
	return (0);
}
