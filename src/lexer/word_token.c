/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 14:56:39 by klakbuic          #+#    #+#             */
/*   Updated: 2024/03/31 00:29:18 by klakbuic         ###   ########.fr       */
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
	if (!token)
	{
		// TODO:
	}
	while (is_word(itr_peek(*itr)) && itr_has_next(*itr))
	{
		token->location.len++;
		itr_next(itr);
	}
	add_token(head, token);
}