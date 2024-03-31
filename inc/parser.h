/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 23:43:10 by soutchak          #+#    #+#             */
/*   Updated: 2024/03/31 06:16:33 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

/* MACROS */
/* ---- */

/* INCLUDES */
# include "common.h"
# include <fcntl.h>
/* ------ */

/* TYPEDEFS */
/* -------- */

/* STRUCTS */
/* -------- */

/* PROTOTYPES */
t_tree	*pipe_add_node(t_tree *pipe, t_tree *node);
t_tree	*pipe_node(void);
t_tree	*exec_node(char **args, int argc, char **env);
t_tree	*redir_node(t_etype type, t_tree *child, char *file);
t_tree *block_node(t_tree *child);
t_tree	*and_or_node(t_etype type, t_tree *left, t_tree *right);

t_tree	*parse_exec(t_token **tokens);
t_tree	*parse_redir(t_token **tokens, t_tree *child);
t_tree	*parse_block(t_token **tokens);
t_tree	*parse_pipe(t_token **tokens);
t_tree	*parse_sequence(t_token **tokens);
t_tree	*parse_sequence_tail(t_token **tokens, t_tree *left);

t_redir	*get_last_redir(t_tree *tree);

// char	*ft_strjoin(char const *s1, char const *s2);
// char	**ft_split(char const *s, char c);
char	*token_type_to_str(t_etype type); // TODO: remove (only for debugging)
/* --------- */

#endif /* PARSER_H */
