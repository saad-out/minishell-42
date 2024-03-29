/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 11:01:14 by klakbuic          #+#    #+#             */
/*   Updated: 2024/03/29 01:16:24 by klakbuic         ###   ########.fr       */
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
typedef enum e_token_type	t_etype;
typedef struct s_slice		t_slice;
typedef char				*t_charitr;
typedef struct s_token		t_token;
/* ------ */

/* ENUMS */
enum						e_token_type
{
	WORD = 1 << 0,
	PIPE = 1 << 1,
	REDIR_IN = 1 << 2,
	REDIR_OUT = 1 << 3,
	APPEND = 1 << 4,
	HEREDOC = 1 << 5,
	WHITESPACE = 1 << 6,
	ENV = 1 << 7,
	AND = 1 << 8,
	OR = 1 << 9,
	LPAR = 1 << 10,
	RPAR = 1 << 11,
	SINGLE_Q = 1 << 12,
	DOUBLE_Q = 1 << 13,
	WILDCARD = 1 << 14,
	LITERAL = 1 << 15,
	BLOCK = 1 << 16,
	UNKNOWN = 1 << 17,
	REDIR = REDIR_IN | REDIR_OUT | APPEND | HEREDOC,
	CTRL = AND | OR,
	STRING = WORD | ENV | WILDCARD | LITERAL,
};
/* ------ */

/* STRUCTS */
struct						s_slice
{
	char					*start;
	size_t					len;
};

struct						s_token
{
	t_etype					type;
	t_slice					location;
	t_token					*prev;
	t_token					*next;
};
/* ------ */

/* PROTOTYPES */
/* Simple string iterator API */
bool						itr_has_next(const t_charitr itr);
char						itr_peek(const t_charitr itr);
char						itr_next(t_charitr *itr);

void						lexer(t_token **tokens, const char *line);
void						print_token(void *data);
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
/* ------ */

#endif