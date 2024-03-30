/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 11:01:14 by klakbuic          #+#    #+#             */
/*   Updated: 2024/03/30 02:26:47 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

/* MACROS */
# define PIPE(c) (c == '|')
# define REDIR_IN(c) (c == '<')
# define REDIR_OUT(c) (c == '>')
# define ENV(c) (c == '$')
# define LPAR(c) (c == '(')
# define RPAR(c) (c == ')')
# define SINGLE_Q(c) (c == '\'')
# define DOUBLE_Q(c) (c == '\"')
# define WILDCARD(c) (c == '*')
# define AND(c) (c == '&')
/* ------ */

/* INCLUDES */
# include "common.h"
/* ------*/

/* TYPEDEFS */
typedef char				*t_charitr;
/* ------ */

/* STRUCTS */
/* ------ */

/* PROTOTYPES */
/* Simple string iterator API */
bool						itr_has_next(const t_charitr itr);
char						itr_peek(const t_charitr itr);
char						itr_next(t_charitr *itr);

void						print_token(t_token *token);
/* Helper functions */
bool						is_whitespace(char c);
bool						is_special(char c);
void						skip_whitespace(t_charitr *itr);
void						whitespace_token(t_token **head, t_charitr *itr);
void						special_tokens(t_token **head, t_charitr *itr);
void						literal_token(t_token **head, t_charitr *itr);
void						word_token(t_token **head, t_charitr *itr);
t_token						*append_new_token(t_token **head, t_etype type,
								char *s, size_t len);
void						add_token(t_token **head, t_token *token);
t_token						*new_token(t_etype type, char *s, size_t len);
/* ------ */

#endif