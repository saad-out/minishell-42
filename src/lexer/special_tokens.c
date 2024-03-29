/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 15:35:33 by klakbuic          #+#    #+#             */
/*   Updated: 2024/03/29 01:05:29 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lexer.h"

static t_token	*greater_append(t_charitr *itr)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	token->location.start = *itr;
	itr_next(itr);
	if (itr_peek(*itr) == '>')
	{
		token->type = APPEND;
		token->location.len = 2;
		itr_next(itr);
	}
	else
	{
		token->type = REDIR_OUT;
		token->location.len = 1;
	}
	return (token);
}

static t_token	*less_heredoc(t_charitr *itr)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	token->location.start = *itr;
	itr_next(itr);
	if (itr_peek(*itr) == '<')
	{
		token->type = HEREDOC;
		token->location.len = 2;
		itr_next(itr);
	}
	else
	{
		token->type = REDIR_IN;
		token->location.len = 1;
	}
	return (token);
}

static t_token	*pipe_or(t_charitr *itr)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	token->location.start = *itr;
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

	token = (t_token *)malloc(sizeof(t_token));
	token->type = WORD;
	token->location.start = *itr;
	token->location.len = 1;
	if (itr_has_next(*itr))
		itr_next(itr);
	if (AND(itr_peek(*itr)))
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

	token = (t_token *)malloc(sizeof(t_token));
	if (token == NULL)
	
	token->location.start = *itr;
	token->location.len = 1;
	if (LPAR(itr_peek(*itr)))
		token->type = LPAR;
	else if (RPAR(itr_peek(*itr)))
		token->type = RPAR;
	else if (WILDCARD(itr_peek(*itr)))
		token->type = WILDCARD;
	else if (ENV(itr_peek(*itr)))
		token->type = ENV;
	itr_next(itr);
	return (token);
}

void	special_tokens(t_token **head, t_charitr *itr)
{
	t_token *token;

	if (PIPE(itr_peek(*itr)))
		token = pipe_or(itr);
	else if (REDIR_IN(itr_peek(*itr)))
		token = less_heredoc(itr);
	else if (REDIR_OUT(itr_peek(*itr)))
		token = greater_append(itr);
	else if (AND(itr_peek(*itr)))
		token = logical_and(itr);
	else
		token = simple_special_tokens(itr);
	add_token(head, token);
}