/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 17:35:23 by soutchak          #+#    #+#             */
/*   Updated: 2024/05/02 18:30:09 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/globals.h"
#include "../inc/memory.h"

void	minishell(void)
{
	char	*line;
	t_token	*tokens;
	t_tree	*tree;

	// init
	ft_init_signals();
	tokens = NULL;
	tree = NULL;
	if (isatty(STDIN_FILENO))
		line = readline(PROMPT);
	else
		line = readline(NULL);
	// For every prompt line
	while (line)
	{
		// history management
		if (line[0] != '\0')
			add_history(line);
		else
		{
			free(line);
			if (isatty(STDIN_FILENO))
				line = readline(PROMPT);
			else
				line = readline(NULL);
			continue ;
		}
		// exit
		// if (strcmp(line, "exit") == 0)
		// TODO: this is simple exit() implementation for testing only
		// 	return (free(line));
		if (strcmp(line, "echo $?") == 0)
		{
			// printf("%d\n", status);
			printf("%d\n", get_exit_status());
			// status = 0;
			set_exit_status(0);
			free(line);
			if (isatty(STDIN_FILENO))
				line = readline(PROMPT);
			else
				line = readline(NULL);
			continue ;
		}
		// debug
		// printf("(%s)\n", line);
		// break line into tokens
		lexer(&tokens, line);
		// print_all_tokens(&tokens);
		if (max_heredoc(tokens))
		{
			ft_putendl_fd("max heredoc exceeded", STDERR_FILENO);
			free(line);
			free_tokens(&tokens);
			exit(2);
		}
		if (syntax_checker(&tokens))
		{
			free(line);
			free_tokens(&tokens);
			if (isatty(STDIN_FILENO))
				line = readline(PROMPT);
			else
				line = readline(NULL);
			continue ;
		}
		post_lexer(&tokens);
		// printf("===> AFTER POST LEXER:\n");
		// print_all_tokens(&tokens);
		// printf("\n");
		// for (t_token *tmp = tokens; tmp; tmp = tmp->next)
		// {
		// 	printf("==> type: %s, str: (", token_type_to_str(tmp->type));
		// 	for (size_t i = 0; i < tmp->location.len; i++)
		// 		printf("%c", tmp->location.start[i]);
		// 	printf(")\n");
		// }
		// parse token into AST
		parser(&tree, tokens);
		// execute command(s)
		executor(tree);
		// cleanup
		free(line);
		// free_tokens(&tokens);
		ft_free_context(LEXER);
		free_tree(tree);
		// reset
		line = NULL;
		tokens = NULL;
		tree = NULL;
		// next iter
		if (isatty(STDIN_FILENO))
			line = readline(PROMPT);
		else
			line = readline(NULL);
	}
}
