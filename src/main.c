/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 17:34:18 by soutchak          #+#    #+#             */
/*   Updated: 2024/03/30 06:36:21 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	**env_ = NULL;
int		status = 0;

int	main(int ac, char **av, char **env)
{
	env_ = env;
	minishell();
	return (0);
}
