/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 00:12:48 by soutchak          #+#    #+#             */
/*   Updated: 2024/05/03 21:31:31 by soutchak         ###   ########.fr       */
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

void	lexer(t_token **head, const char *line)
{
	t_charitr	itr;

	itr = (t_charitr)line;
	while (itr_has_next(itr))
	{
		if (is_whitespace(itr_peek(itr)))
			whitespace_token(head, &itr);
		else if (is_special(itr_peek(itr)))
			special_tokens(head, &itr);
		else if (itr_peek(itr) == '\"' || itr_peek(itr) == '\'')
			literal_token(head, &itr);
		else
			word_token(head, &itr);
	}
}
