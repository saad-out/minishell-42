/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 00:40:16 by klakbuic          #+#    #+#             */
/*   Updated: 2024/05/03 19:00:41 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/globals.h"
#include "../../inc/lexer.h"
#include "../../inc/minishell.h"

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

static bool	paran_check(t_token *token, t_token **tokens)
{
	t_etype	prev_type;
	t_etype	next_type;

	if (paran_check_nb(tokens) == false)
	{
		ft_putstr_fd(RED, STDERR_FILENO);
		return (ft_putendl_fd(ERR_PARAN, STDERR_FILENO), false);
	}
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
		ft_putstr_fd(ERR_UNEXPECTED_TOKEN, STDERR_FILENO);
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
		ft_putendl_fd(ERR_QUOTES, STDERR_FILENO);
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
			error = paran_check(token, tokens);
		else if (token->type & REDIR)
			error = redir_check(token);
		else if (token->type & QUOTES)
			error = quotes_check(token);
		if (error)
			break ;
		move_qoute_token(&token);
		token = token->next;
	}
	if (error)
		set_exit_status(SYNTAX_ERR_STATUS);
	return (error);
}
