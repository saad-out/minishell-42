/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   literals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 14:00:31 by klakbuic          #+#    #+#             */
/*   Updated: 2024/03/30 01:15:45 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lexer.h"

static void	single_quote(t_token **head, t_charitr *itr)
{
	t_token	*token;

	token = new_token(SINGLE_Q, *itr, 1);
	if (!token)
	{
		// TODO:
	}
	if (itr_has_next(*itr))
		itr_next(itr);
	//print_token(token);
	add_token(head, token);
}

static void	single_quote_literal(t_token **head, t_charitr *itr)
{
	t_token	*token;

	if (itr_peek(*itr) == '\'')
		return ;
	token = new_token(LITERAL, *itr, 0);
	if (!token)
	{
		// TODO:
	}
	while (itr_has_next(*itr) && (itr_peek(*itr) != '\''))
	{
		itr_next(itr);
		token->location.len++;
	}
	//print_token(token);
	add_token(head, token);
	if (itr_peek(*itr) == '\'')
		single_quote(head, itr);
}

static void	double_quote(t_token **head, t_charitr *itr)
{
	t_token	*token;

	token = new_token(DOUBLE_Q, *itr, 1);
	if (!token)
	{
		// TODO:
	}
	if (itr_has_next(*itr))
		itr_next(itr);
	//print_token(token);
	add_token(head, token);
}

static void	double_quote_literal(t_token **head, t_charitr *itr)
{
	t_token	*token;

	if (itr_peek(*itr) == '\"')
		return ;
	token = new_token(LITERAL, *itr, 0);
	if (!token)
	{
		// TODO:
	}
	while (itr_has_next(*itr) && (itr_peek(*itr) != '\"'))
	{
		itr_next(itr);
		token->location.len++;
	}
	//print_token(token);
	add_token(head, token);
	if (itr_peek(*itr) == '\"')
		double_quote(head, itr);
}

void	literal_token(t_token **head, t_charitr *itr)
{
	if (itr_peek(*itr) == '\"')
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
