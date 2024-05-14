/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 01:48:47 by soutchak          #+#    #+#             */
/*   Updated: 2024/05/05 16:15:45 by soutchak         ###   ########.fr       */
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
t_env	**get_env_list(void);
int		*heredoc_error(void);
/* --------- */

#endif /* GLOBALS_H */
