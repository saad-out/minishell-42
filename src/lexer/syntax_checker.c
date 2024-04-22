/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 00:40:16 by klakbuic          #+#    #+#             */
/*   Updated: 2024/04/22 10:39:50 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/common.h"
#include "../../inc/lexer.h"

static bool	quotes_checker(t_token **tokens)
{
	t_token	*head;
	int		nb_single_q;
	int		nb_double_q;

	head = *tokens;
	nb_single_q = 0;
	nb_double_q = 0;
	while (head)
	{
		if (head->type == SINGLE_Q)
			nb_single_q++;
		if (head->type == DOUBLE_Q)
			nb_double_q++;
		head = head->next;
	}
	if (nb_single_q % 2 || nb_double_q % 2)
		return (true);
	return (false);
}

static t_etype	get_next_type(t_token *token)
{
	if (token->next)
	{
		if (token->next->type == WHITESPACE)
		{
			if (token->next->next)
				return (token->next->next->type);
			return (VOID);
		}
		else
			return (token->next->type);
	}
	return (VOID);
}

static t_etype	get_prev_type(t_token *token)
{
	if (token->prev)
	{
		if (token->prev->type == WHITESPACE)
		{
			if (token->prev->prev)
				return (token->prev->prev->type);
			return (VOID);
		}
		else
			return (token->prev->type);
	}
	return (VOID);
}
static void	print_error(t_token *token)
{
	ft_putstr_fd("syntax error near unexpected token `", STDOUT_FILENO);
	write(STDOUT_FILENO, token->location.start, token->location.len);
	ft_putendl_fd("\"", STDOUT_FILENO);
}

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
	if (!(next_type & (QUOTES | WILDCARD | ENV | WORD | REDIR | RPAR)))
	{
		print_error(token);
		return (true);
	}
	return (false);
}

bool	syntax_checker(t_token **tokens)
{
	t_token *token;
	bool error;

	error = false;
	token = *tokens;
	while (token)
	{
		if (token->type & (PIPE | CTRL))
			error = and_or_pipe_check(token);
		if (error)
			return (true);
		token = token->next;
	}
	return (error);
}