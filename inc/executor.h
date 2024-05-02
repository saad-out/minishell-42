/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 23:43:10 by soutchak          #+#    #+#             */
/*   Updated: 2024/05/02 15:53:09 by soutchak         ###   ########.fr       */
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
void	print_all_env(t_env *envs, bool env_ex);
/* --- Builtins --- */
int (*is_builtin(char *cmd))(t_exec *exec);
int		ft_echo(t_exec *cmd);
int		ft_pwd(t_exec *cmd);
int		ft_cd(t_exec *cmd);
int		ft_unset(t_exec *cmd);
int		ft_exit(t_exec *exec);
int		ft_env(t_exec *cmd);
int		ft_export(t_exec *cmd);

int	check_paths(char *full_path);
/* --------- */

#endif /* EXECUTOR_H */