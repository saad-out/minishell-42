/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 14:56:39 by klakbuic          #+#    #+#             */
/*   Updated: 2024/05/02 18:57:30 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lexer.h"

bool	is_quotes(char c)
{
	return (c == '\'' || c == '\"');
}

bool	is_word(char c)
{
	return (!is_whitespace(c) && !is_special(c) && !is_quotes(c));
}

void	word_token(t_token **head, t_charitr *itr)
{
	t_token	*token;

	token = new_token(WORD, *itr, 0);
	while (is_word(itr_peek(*itr)) && itr_has_next(*itr))
	{
		token->location.len++;
		itr_next(itr);
	}
	add_token(head, token);
}
