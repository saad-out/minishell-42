/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 14:56:39 by klakbuic          #+#    #+#             */
/*   Updated: 2024/03/29 01:05:29 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lexer.h"

static bool	is_word(char c)
{
	return (!is_whitespace(c) && !is_special(c));
}

void	word_token(t_token **head, t_charitr *itr)
{
	t_token *token;

	token = (t_token *)malloc(sizeof(t_token));
	token->type = WORD;
	token->location.start = *itr;
	token->location.len = 0;
	while (is_word(itr_peek(*itr)) && itr_has_next(*itr))
	{
		token->location.len++;
		itr_next(itr);
	}
	add_token(head, token);
}