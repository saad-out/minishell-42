/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:40:00 by soutchak          #+#    #+#             */
/*   Updated: 2024/04/29 16:26:17 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBALS_H
# define GLOBALS_H

/* INCLUDES */
# include "common.h"
/* ------- */

/* PROTOTYPES */
int		get_exit_status(void);
void	set_exit_status(int status);
t_env 	**get_env_list(void);
/* --------- */

#endif /* GLOBALS_H */
