/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 15:35:33 by klakbuic          #+#    #+#             */
/*   Updated: 2024/05/01 09:46:27 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lexer.h"

static t_token	*pipe_or(t_charitr *itr)
{
	t_token	*token;

	token = new_token(UNKNOWN, *itr, 0);
	itr_next(itr);
	if (itr_peek(*itr) == '|')
	{
		token->type = OR;
		token->location.len = 2;
		itr_next(itr);
	}
	else
	{
		token->type = PIPE;
		token->location.len = 1;
	}
	return (token);
}

static t_token	*logical_and(t_charitr *itr)
{
	t_token	*token;

	token = new_token(WORD, *itr, 1);
	if (itr_has_next(*itr))
		itr_next(itr);
	if (itr_peek(*itr) == '&')
	{
		token->type = AND;
		token->location.len++;
		if (itr_has_next(*itr))
			itr_next(itr);
	}
	return (token);
}

static t_token	*simple_special_tokens(t_charitr *itr)
{
	t_token	*token;

	token = new_token(UNKNOWN, *itr, 1);
	if (itr_peek(*itr) == '(')
		token->type = LPAR;
	else if (itr_peek(*itr) == ')')
		token->type = RPAR;
	else if (itr_peek(*itr) == '*')
		token->type = WILDCARD;
	else if (itr_peek(*itr) == '$')
		token->type = ENV;
	itr_next(itr);
	return (token);
}

void	special_tokens(t_token **head, t_charitr *itr)
{
	t_token	*token;

	if (itr_peek(*itr) == '|')
		token = pipe_or(itr);
	else if (itr_peek(*itr) == '<')
		token = less_heredoc(itr);
	else if (itr_peek(*itr) == '>')
		token = greater_append(itr);
	else if (itr_peek(*itr) == '&')
		token = logical_and(itr);
	else
		token = simple_special_tokens(itr);
	add_token(head, token);
}
