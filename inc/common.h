/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 23:43:10 by soutchak          #+#    #+#             */
/*   Updated: 2024/03/29 01:15:30 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H

/* MACROS */
# ifndef PROMPT
#  define PROMPT "Minishell$> "
# endif /* PROMPT */
/* ---- */

/* INCLUDES */
# include "../libs/libft/libft.h"
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
/* ------ */

/* TYPEDEFS */
typedef void t_tree; // TODO: remove (only for debugging)
/* -------- */

/* ENUMS */

/* ---- */

/* PROTOTYPES */
void	*getmem(size_t size);
// void						minishell(void);
// void						lexer(t_list **lst, char *line);
// void						executor(t_tree *tree);
// void						parser(t_tree **tree, t_token *tokens);
// t_token						*new_token(t_etype type, char *s);
// void						add_token(t_token **head, t_token *token);
// t_token						*append_new_token(t_token **head, t_etype type,
// 								char *s);
// void						free_tokens(t_token **token_list);
/* --------- */

#endif /* HEADER_H */