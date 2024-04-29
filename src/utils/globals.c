/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:37:50 by soutchak          #+#    #+#             */
/*   Updated: 2024/04/29 16:26:11 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/globals.h"

static int	*get_exit_status_g(void)
{
	static int	status = 0;

	return (&status);
}

void	set_exit_status(int status)
{
	*get_exit_status_g() = status;
}

int	get_exit_status(void)
{
	return (*get_exit_status_g());
}

t_env **get_env_list(void)
{
	static t_env	*env = NULL;

	return (&env);
}
