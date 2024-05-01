/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 23:43:10 by soutchak          #+#    #+#             */
/*   Updated: 2024/05/01 08:35:00 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H
# define READLINE_LIBRARY

/* MACROS */
# define SIZE 4096

# ifndef MANY_ARGS_ERROR
#  define MANY_ARGS_ERROR "Too many argument!"
# endif /* MANY_ARGS_ERROR */

# ifndef MAX_STATUS_LEN
#  define MAX_STATUS_LEN 19
# endif /* MAX_STATUS_LEN */

# ifndef DECLARE
#  define DECLARE "declare -x "
# endif /* DECLARE */
/* ---- */

/* INCLUDES */
// # include "../libs/ft_containers/ft_data_structres.h"
# include "libs.h"
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <unistd.h>
// # include <readline/history.h>
// # include <readline/readline.h>
# include "/Users/klakbuic/readline/include/readline/readline.h"
# include "/Users/klakbuic/readline/include/readline/history.h"
/* ------ */

/* TYPEDEFS */
typedef struct s_slice		t_slice;
typedef enum e_token_type	t_etype;
typedef struct s_token		t_token;
typedef struct s_tree		t_tree;
typedef struct s_and_or		t_and_or;
typedef struct s_block		t_block;
typedef struct s_pipe		t_pipe;
typedef struct s_exec		t_exec;
typedef struct s_redir		t_redir;
typedef struct s_env		t_env;
typedef enum e_visibility	t_visibility;
/* -------- */

/* GLOBALS */
extern t_env				*env_;
extern int					status;
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
	EXEC = 1 << 17,
	UNKNOWN = 1 << 18,
	VOID = 1 << 19,
	PARAN = LPAR | RPAR,
	QUOTES = SINGLE_Q | DOUBLE_Q,
	REDIR = REDIR_IN | REDIR_OUT | APPEND | HEREDOC,
	CTRL = AND | OR,
	STRING = WORD | ENV | WILDCARD | LITERAL,
	CONNECTORS = PIPE | AND | OR | LPAR,
};

enum						e_visibility
{
	ENVE = 1 << 0,
	EXPORT = 1 << 1,
	BOTH = 1 << 2,
	SPECIAL = 1 << 3
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

struct						s_tree
{
	t_etype					type;
};

struct						s_and_or
{
	t_etype					type;
	t_tree					*left;
	t_tree					*right;
};

struct						s_block
{
	t_etype					type;
	t_tree					*child;
};

struct						s_pipe
{
	t_etype					type;
	size_t					nb_pipes;
	t_tree					*nodes[10];
	// t_tree			**nodes;
};

struct						s_redir
{
	t_etype					type;
	int						fd;
	char					*file;
	int flags;   // O_RDONLY, O_WRONLY, O_CREAT, O_APPEND
	mode_t mode; // S_IRUSR, S_IWUSR, S_IRGRP, S_IROTH ==> leave to default
	bool					expand;
	t_tree					*child;
};

struct						s_exec
{
	t_etype					type;
	char					**argv;
	int						argc;
	// char					**env;
	t_env					**env;
};

struct						s_env
{
	char					*key;
	char					*value;
	t_visibility			visibility;
	bool					masked;
	t_env					*prev;
	t_env					*next;
};

/* ------ */

/* PROTOTYPES */
void						minishell(void);
void						free_tokens(t_token **token_list);
void						free_tree(t_tree *tree);
void						executor(t_tree *tree);

/* -- ENVS ---*/
t_env						*build_env(char **env);
char						*get_env_value(t_env *envs, const char *key);
t_env						*get_env(t_env *envs, const char *key);
void						set_env(t_env *envs, const char *key,
								const char *new_value);
void						add_env_char(t_env **envs, char *key, char *value);
char						**rebuild_env_to_char(t_env *envs);
void						set_under(char **argv, int argc);

/* --------- */
void						ft_init_signals(void);
void						interrput_handler_2(int sig);
void						interrput_handler_3(int sig);

#endif /* HEADER_H */
