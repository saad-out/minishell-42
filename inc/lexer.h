/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 11:01:14 by klakbuic          #+#    #+#             */
/*   Updated: 2024/05/04 01:49:37 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

/* INCLUDES */
# include "common.h"
# include "minishell.h"
/* ------*/

/* MACROS */
# ifndef SYNTAX_ERR_STATUS
#  define SYNTAX_ERR_STATUS 258
# endif /* SYNTAX_ERR_STATUS */

# ifndef ERR_UNEXPECTED_TOKEN
#  define ERR_UNEXPECTED_TOKEN "\033[0;31moutlaakSH: \
								syntax error near unexpected token `"
# endif /* ERR_UNEXPECTED_TOKEN */

# ifndef ERR_PARAN
#  define ERR_PARAN "\033[0;31moutlaakSH: syntax error, unclosed parentheses"
# endif /* ERR_PARAN */

# ifndef ERR_QUOTES
#  define ERR_QUOTES "\033[0;31moutlaakSH: syntax error, unclosed quotes"
# endif /* ERR_QUOTES */

/* ------ */

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
t_token			*less_heredoc(t_charitr *itr);
t_token			*greater_append(t_charitr *itr);
/* --- doubly linked list functions --- */
t_token			*append_new_token(t_token **head, t_etype type, char *s,
					size_t len);
void			add_token(t_token **head, t_token *token);
t_token			*new_token(t_etype type, char *s, size_t len);

/* --- Sytax error*/
bool			syntax_checker(t_token **tokens);
void			remove_token(t_token **head, t_token *token);
void			move_qoute_token(t_token **token);
bool			paran_check_nb(t_token **tokens);
t_etype			get_next_type(t_token *token);
t_etype			get_prev_type(t_token *token);
void			print_error(t_token *token);
#endif