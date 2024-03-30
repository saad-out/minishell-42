/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 23:43:10 by soutchak          #+#    #+#             */
/*   Updated: 2024/03/30 06:49:37 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
#define EXECUTOR_H

/* INCLUDES */
# include "common.h"
# include <fcntl.h>
# include <errno.h>
/* ------- */

/* GLOBALS */
extern char	**env_;
/* ------ */

/* PROTOTYPES */
int	    spawn_process(int input, int output, t_tree *tree);
char	*get_cmd_path(char *cmd);
/* --------- */

#endif /* EXECUTOR_H */