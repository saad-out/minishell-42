/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 11:01:14 by klakbuic          #+#    #+#             */
/*   Updated: 2024/04/22 10:36:34 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

/* MACROS */

/* ------ */

/* INCLUDES */
# include "common.h"
/* ------*/

/* TYPEDEFS */
typedef char	*t_charitr;
/* ------ */

/* STRUCTS */
/* ------ */

/* PROTOTYPES */
/* Simple string iterator API */
bool			itr_has_next(const t_charitr itr);
char			itr_peek(const t_charitr itr);
char			itr_next(t_charitr *itr);
void			print_token(t_token *token);

/* --- Boolean functions --- */
bool			is_whitespace(char c);
bool			is_special(char c);
bool			is_quotes(char c);

/* --- make tokens functions --- */
void			skip_whitespace(t_charitr *itr);
void			whitespace_token(t_token **head, t_charitr *itr);
void			special_tokens(t_token **head, t_charitr *itr);
void			literal_token(t_token **head, t_charitr *itr);
void			word_token(t_token **head, t_charitr *itr);

/* --- doubly linked list functions --- */
t_token			*append_new_token(t_token **head, t_etype type, char *s,
					size_t len);
void			add_token(t_token **head, t_token *token);
t_token			*new_token(t_etype type, char *s, size_t len);

/* --- Sytax error*/
bool	syntax_checker(t_token **tokens);

void	remove_token(t_token **head, t_token *token);

#endif