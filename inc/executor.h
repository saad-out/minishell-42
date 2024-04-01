/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 23:43:10 by soutchak          #+#    #+#             */
/*   Updated: 2024/03/31 05:23:02 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
#define EXECUTOR_H

/* INCLUDES */
# include "common.h"
# include <fcntl.h>
# include <errno.h>
/* ------- */

/* PROTOTYPES */
pid_t	spawn_process(int input, int output, t_tree *tree);
char	*get_cmd_path(char *cmd);
int		get_status(t_tree *tree);
/* --------- */

#endif /* EXECUTOR_H */