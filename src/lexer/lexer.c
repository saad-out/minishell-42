/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 00:12:48 by soutchak          #+#    #+#             */
/*   Updated: 2024/03/29 15:59:57 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lexer.h"

bool	is_special(char c)
{
	if (c == '|' || c == '<' || c == '>' || c == '$' || c == '(' || c == ')'
		|| c == '*' || c == '&')
		return (true);
	return (false);
}

// static bool	is_simple_special(char c)
// {
// 	if (LPAR(c) || RPAR(c) || ENV(c) || WILDCARD(c))
// 		return (true);
// 	return (false);
// }

/* for the functions that will be used in just one file it's a good practice to make them static ;) */
void	lexer(t_token **head, const char *line)
{
	t_charitr	itr;
	t_token		*token;

	itr = (t_charitr)line;
	while (itr_has_next(itr))
	{
		// printf("peek:---------------|%c|\n", itr_peek(itr));
		// TODO: making all of this fucntions returning void and managmen failure !!!
		if (is_whitespace(itr_peek(itr)))
		{
			// puts("White");
			whitespace_token(head, &itr);
		}
		else if (is_special(itr_peek(itr)))
		{
			// puts("Special");
			special_tokens(head, &itr);
		}
		else if (itr_peek(itr) == '\"' || itr_peek(itr) == '\'')
		{
			// puts("Literal");
			literal_token(head, &itr);
		}
		else
		{
			// puts("Word");
			word_token(head, &itr);
		}
	}
	// printf("token :%p\n", token);
}
