/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 23:43:10 by soutchak          #+#    #+#             */
/*   Updated: 2024/03/30 02:35:34 by soutchak         ###   ########.fr       */
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
typedef struct s_and_or		t_and_or;
typedef struct s_block		t_block;
typedef struct s_pipe		t_pipe;
typedef struct s_exec		t_exec;
typedef struct s_redir		t_redir;
/* -------- */

/* STRUCTS */
struct s_and_or
{
	t_etype	type;
	t_tree	*left;
	t_tree	*right;
};

struct s_block
{
	t_etype	type;
	t_tree	*child;
};

struct s_pipe
{
	t_etype			type;
	size_t			nb_pipes;
	t_tree			*nodes[10];
	// t_tree			**nodes;
};

struct s_redir
{
	t_etype			type;
	int				fd;
	char			*file;
	int				flags;	// O_RDONLY, O_WRONLY, O_CREAT, O_APPEND
	mode_t			mode;	// S_IRUSR, S_IWUSR, S_IRGRP, S_IROTH ==> leave to default
	t_tree			*child;
};

struct s_exec
{
	t_etype			type;
	char			**argv;
	int				argc;
	char			**env;
};
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

// char	*ft_strjoin(char const *s1, char const *s2);
// char	**ft_split(char const *s, char c);
char	*token_type_to_str(t_etype type); // TODO: remove (only for debugging)
/* --------- */

#endif /* PARSER_H */
