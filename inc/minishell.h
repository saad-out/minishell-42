/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 17:31:17 by soutchak          #+#    #+#             */
/*   Updated: 2024/03/30 05:08:34 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* MARCORS */
# ifndef PROMPT
#  define PROMPT "Minishell$> "
# endif /* PROMPT */
/* ----- */

/* INCLUDES */
# include "common.h"
# include <readline/history.h>
# include <readline/readline.h>
/* ------- */

/* PROTOTYPES */
void	lexer(t_token **tokens, const char *line);
void	post_lexer(t_token **tokens);
void	parser(t_tree **tree, t_token *tokens);
// void	executor(t_tree *tree);
void	visit_tree(t_tree *tree, int depth);

char	*token_type_to_str(t_etype type); // TODO: remove (only for debugging)
/* --------- */

#endif /* MINISHELL_H */