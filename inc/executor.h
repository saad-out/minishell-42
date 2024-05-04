/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 23:43:10 by soutchak          #+#    #+#             */
/*   Updated: 2024/05/03 23:01:20 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

/* INCLUDES */
# include "common.h"
# include <errno.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
/* ------- */

/* PROTOTYPES */
pid_t	spawn_process(int input, int output, t_tree *tree);
char	*get_cmd_path(char *cmd);
int		get_status(t_tree *tree);
void	print_all_env(t_env *envs, bool env_ex);
void	free_tab(char **tab);
void	sort_envs(t_env **envs);

/* --- Builtins --- */
int (*is_builtin(char *cmd))(t_exec *exec);
int		ft_echo(t_exec *cmd);
int		ft_pwd(t_exec *cmd);
int		ft_cd(t_exec *cmd);
int		ft_unset(t_exec *cmd);
int		ft_exit(t_exec *exec);
int		ft_env(t_exec *cmd);
int		ft_export(t_exec *cmd);

int	    check_paths(char *full_path);
pid_t	lunch_pipes(t_pipe *pipe_node);
int	    run_from_path(t_exec *exec);
int	    run_exec(t_exec *exec);
int	    check_cmd(t_exec *exec);
void	child(t_exec *exec);
int	    parent(t_exec *exec);

int	    run_ctrl(t_tree *tree);
int	    run_block(t_tree *tree);
int	    run_pipe(t_tree *tree);
int	    run_redir(t_tree *tree);
int	    run_cmd(t_tree *tree);
/* --------- */

#endif /* EXECUTOR_H */