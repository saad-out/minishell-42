/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 17:35:23 by soutchak          #+#    #+#             */
/*   Updated: 2024/03/28 17:36:32 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "parser.h"

void	minishell(void)
{
	char	*line;
	t_token	*tokens;
	t_tree	*tree;

	// init
	tokens = NULL;
	tree = NULL;
	line = readline(PROMPT);

	// For every prompt line
	while (line)
	{
		// history management
		if (line[0] != '\0')
			add_history(line);
		else
		{
			free(line);
			line = readline(PROMPT);
			continue ;
		}

		// exit
		if (strcmp(line, "exit") == 0) // TODO: this is simple exit() implementation for testing only
			return (free(line));
		
		// debug
		printf("(%s)\n", line);
		
		// break line into tokens
		lexer(&tokens, line);

		for (t_token *tmp = tokens; tmp; tmp = tmp->next)
		{
			printf("==> type: %s, str: (", token_type_to_str(tmp->type));
			for (size_t i = 0; i < tmp->len; i++)
				printf("%c", tmp->str[i]);
			printf(")\n");
		}
	
		// parse token into AST
		parser(&tree, tokens);
		// printf("we are here\n\n");
		// print_tree(tree);
		printf("\n====================\n\n");
		visit_tree(tree, 0);

		// execute command(s)
		executor(tree);
		
		// cleanup
		free(line);
		free_tokens(&tokens);
		// free_tree(tree);

		// next iter
		line = readline(PROMPT);
	}
}
