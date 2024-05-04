/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 17:35:23 by soutchak          #+#    #+#             */
/*   Updated: 2024/05/04 01:34:57 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/globals.h"
#include "../inc/memory.h"

static void	init(t_token **tokens, t_tree **tree)
{
	ft_init_signals();
	*tokens = NULL;
	*tree = NULL;
}

static void	free_contexts(void)
{
	ft_free_context(LEXER);
	ft_free_context(PARSER);
	ft_free_context(EXECUTOR);
	ft_free_context(EXPANDER);
}

static char	*ft_readline(char *prev_line)
{
	char	*line;

	line = NULL;
	if (prev_line)
		free(prev_line);
	if (isatty(STDIN_FILENO))
		line = readline(PROMPT);
	else
		line = readline(NULL);
	return (line);
}

static void	parse_and_execute(t_token **tokens, t_tree **tree, char *line)
{
	lexer(tokens, line);
	if (max_heredoc(*tokens))
	{
		ft_putendl_fd("max heredoc exceeded", STDERR_FILENO);
		return (free(line), ft_free_heap(), exit(2));
	}
	if (syntax_checker(tokens))
		return ;
	post_lexer(tokens);
	parser(tree, *tokens);
	executor(*tree);
}

void	minishell(void)
{
	char	*line;
	t_token	*tokens;
	t_tree	*tree;

	init(&tokens, &tree);
	line = NULL;
	line = ft_readline(line);
	while (line)
	{
		if (line[0] != '\0')
			add_history(line);
		else
		{
			free_contexts();
			line = ft_readline(line);
			continue ;
		}
		parse_and_execute(&tokens, &tree, line);
		free_contexts();
		init(&tokens, &tree);
		line = ft_readline(line);
	}
}
