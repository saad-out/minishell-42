/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 17:31:17 by soutchak          #+#    #+#             */
/*   Updated: 2024/05/04 01:57:09 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* MARCORS */
# ifndef YELLOW
#  define YELLOW "\033[0;33m"
# endif /* YELLOW */

# ifndef RED
#  define RED "\033[0;31m"
# endif /* RED */

# ifndef GREEN
#  define GREEN "\033[0;32m"
# endif /* GREEN */

# ifndef BLUE
#  define BLUE "\033[0;34m"
# endif /* BLUE */

# ifndef CYAN
#  define CYAN "\033[0;36m"
# endif /* CYAN */

# ifndef MAGENTA
#  define MAGENTA "\033[0;35m"
# endif /* MAGENTA */

# ifndef RESET
#  define RESET "\033[0m"
# endif /* RESET */

# ifndef PROMPT
#  define PROMPT "outlaakSH$> "
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
bool	max_heredoc(t_token *tokens);
bool	syntax_checker(t_token **tokens);
/* --------- */

#endif /* MINISHELL_H */