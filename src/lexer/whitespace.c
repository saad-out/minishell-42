/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whitespace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 14:45:34 by klakbuic          #+#    #+#             */
/*   Updated: 2024/03/28 23:49:40 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lexer.h"

bool	is_whitespace(char c)
{
	return (c == ' ' || c == '\t');
}

void	skip_whitespace(t_charitr *itr)
{
	while (itr_has_next(*itr) && is_whitespace(itr_peek(*itr)))
		itr_next(itr);
}

void	whitespace_token(t_token **head, t_charitr *itr)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	token->location.start = *itr;
	token->location.len = 0;
	token->type = WHITESPACE;
	while (itr_has_next(*itr) && is_whitespace(itr_peek(*itr)))
	{
		itr_next(itr);
		token->location.len++;
	}
	add_token(head, token);
}
