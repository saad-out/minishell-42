/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whitespace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 14:45:34 by klakbuic          #+#    #+#             */
/*   Updated: 2024/03/31 00:29:07 by klakbuic         ###   ########.fr       */
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

	token = new_token(WHITESPACE, *itr, 0);
	if (!token)
	{
		// TODO:
	}
	while (itr_has_next(*itr) && is_whitespace(itr_peek(*itr)))
	{
		itr_next(itr);
		token->location.len++;
	}
	//print_token(token);
	add_token(head, token);
}