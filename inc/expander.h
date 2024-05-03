
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 16:19:03 by soutchak          #+#    #+#             */
/*   Updated: 2024/04/26 16:08:26 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

/* MARCROS */
/* ------ */

/* INCLUDES */
# include "common.h"
# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
/* ------- */

/* PROTOTYPES */
void	expander(t_tree *node);
void	expand_vars(t_tree *node);
char	*expand_var(char *var, int *i);
char	*expand_double_q(char *s, int *i);
char	*expand_single_q(char *s, int *i);
void	expand_wildcards(t_tree *node);
void	expand_heredoc(t_redir *redir);
char	*get_next_line(int fd);
char	*join_var(char *joined, char *s, int *i);
char	*join_regular(char *joined, char *s, int *i, const char *set);
void	add_to_argv(char ***argv, char *s, int *argc, bool splt);
void	expand_exec_vars(t_exec *exec);
void	expand_redir_vars(t_redir *redir);
int	    count_words(char **words);
bool	to_expand(char c);
/* --------- */

#endif /* EXPANDER_H */
