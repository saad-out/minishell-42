/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 00:40:16 by klakbuic          #+#    #+#             */
/*   Updated: 2024/05/02 08:47:58 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/globals.h"
#include "../../inc/lexer.h"

static bool	and_or_pipe_check(t_token *token)
{
	t_etype	prev_type;
	t_etype	next_type;

	prev_type = get_prev_type(token);
	if (!(prev_type & (QUOTES | WILDCARD | ENV | WORD | RPAR)))
	{
		print_error(token);
		return (true);
	}
	next_type = get_next_type(token);
	if (!(next_type & (QUOTES | WILDCARD | ENV | WORD | REDIR | LPAR)))
	{
		print_error(token);
		return (true);
	}
	return (false);
}

static bool	paran_check(t_token *token)
{
	t_etype	prev_type;
	t_etype	next_type;

	prev_type = get_prev_type(token);
	next_type = get_next_type(token);
	if (token->type == LPAR)
	{
		if (!(prev_type & (VOID | PIPE | CTRL | LPAR)))
			return (print_error(token), true);
		if (!(next_type & (QUOTES | ENV | WORD | WILDCARD | REDIR | LPAR)))
			return (print_error(token), true);
	}
	else
	{
		if (!(prev_type & (QUOTES | ENV | WORD | WILDCARD | RPAR)))
			return (print_error(token), true);
		if (!(next_type & (VOID | PIPE | CTRL | REDIR | RPAR)))
			return (print_error(token), true);
	}
	return (false);
}

static bool	redir_check(t_token *token)
{
	t_etype	next_type;

	next_type = get_next_type(token);
	if (!(next_type & (QUOTES | ENV | WILDCARD | WORD)))
	{
		ft_putstr_fd("syntax error near unexpected token `", STDERR_FILENO);
		ft_putendl_fd("newline'", STDERR_FILENO);
		return (true);
	}
	return (false);
}

static bool	quotes_check(t_token *token)
{
	t_etype	next_type;

	next_type = get_next_type(token);
	if (next_type == LITERAL)
	{
		if (token->next->next)
			next_type = get_next_type(token->next);
	}
	if (token->type != next_type)
	{
		ft_putendl_fd("Unclosed quotes", STDERR_FILENO);
		return (true);
	}
	return (false);
}

bool	syntax_checker(t_token **tokens)
{
	t_token	*token;
	bool	error;

	error = false;
	token = *tokens;
	while (token)
	{
		if (token->type & (PIPE | CTRL))
			error = and_or_pipe_check(token);
		else if (token->type & PARAN)
			error = paran_check(token);
		else if (token->type & REDIR)
			error = redir_check(token);
		else if (token->type & QUOTES)
			error = quotes_check(token);
		if (error)
			return (true);
		if (token->type & QUOTES)
		{
			token = token->next;
			if (token && token->type == LITERAL)
				token = token->next;
		}
		token = token->next;
	}
	return (set_exit_status(SYNTAX_ERR_STATUS), error);
}
