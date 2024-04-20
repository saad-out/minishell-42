/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 23:43:10 by soutchak          #+#    #+#             */
/*   Updated: 2024/04/20 18:59:22 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

/* INCLUDES */
# include "common.h"
# include <errno.h>
# include <fcntl.h>
/* ------- */

/* PROTOTYPES */
pid_t	spawn_process(int input, int output, t_tree *tree);
char	*get_cmd_path(char *cmd);
int		get_status(t_tree *tree);
/* --- Builtins --- */
int (*is_builtin(char *cmd))(t_exec *exec);
int		ft_echo(t_exec *cmd);
int		ft_pwd(t_exec *cmd);
int		ft_cd(t_exec *cmd);
int		ft_unset(t_exec *cmd);
int		ft_exit(t_exec *exec);
int		ft_env(t_exec *cmd);
/* --------- */

#endif /* EXECUTOR_H */