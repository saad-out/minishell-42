/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   literals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 14:00:31 by klakbuic          #+#    #+#             */
/*   Updated: 2024/03/29 01:19:43 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lexer.h"

static void	single_quote(t_token **head, t_charitr *itr)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	token->location.start = *itr;
	token->location.len = 1;
	token->type = SINGLE_Q;
	if (itr_has_next(*itr))
		itr_next(itr);
	add_token(head, token);
}

static void	single_quote_literal(t_token **head, t_charitr *itr)
{
	t_token	*token;

	if (SINGLE_Q(itr_peek(*itr)))
		return ;
	token = (t_token *)malloc(sizeof(t_token));
	token->location.start = *itr;
	token->type = LITERAL;
	token->location.len = 0;
	while (itr_has_next(*itr) && !SINGLE_Q(itr_peek(*itr)))
	{
		itr_next(itr);
		token->location.len++;
	}
	add_token(head, token);
	if (SINGLE_Q(itr_peek(*itr)))
		single_quote(head, itr);
}

static void	double_quote(t_token **head, t_charitr *itr)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	token->location.start = *itr;
	token->location.len = 1;
	token->type = DOUBLE_Q;
	if (itr_has_next(*itr))
		itr_next(itr);
	add_token(head, token);
}

static void	double_quote_literal(t_token **head, t_charitr *itr)
{
	t_token	*token;

	if (DOUBLE_Q(itr_peek(*itr)))
		return ;
	token = (t_token *)malloc(sizeof(t_token));
	token->location.start = *itr;
	token->type = LITERAL;
	token->location.len = 0;
	while (itr_has_next(*itr) && !DOUBLE_Q(itr_peek(*itr)))
	{
		itr_next(itr);
		token->location.len++;
	}
	add_token(head, token);
	if (DOUBLE_Q(itr_peek(*itr)))
		double_quote(head, itr);
}

void	literal_token(t_token **head, t_charitr *itr)
{
	if (DOUBLE_Q(itr_peek(*itr)))
	{
		double_quote(head, itr);
		double_quote_literal(head, itr);
	}
	else
	{
		single_quote(head, itr);
		single_quote_literal(head, itr);
	}
	// print_token((void *)token);
}
