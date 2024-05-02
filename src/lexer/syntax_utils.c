/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:51:13 by klakbuic          #+#    #+#             */
/*   Updated: 2024/05/02 18:53:34 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/common.h"
#include "../../inc/lexer.h"

t_etype	get_next_type(t_token *token)
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

t_etype	get_prev_type(t_token *token)
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

void	print_error(t_token *token)
{
	ft_putstr_fd(ERR_UNEXPECTED_TOKEN, STDERR_FILENO);
	write(STDOUT_FILENO, token->location.start, token->location.len);
	ft_putendl_fd("'", STDERR_FILENO);
}

void	move_qoute_token(t_token **token)
{
	if ((*token)->type & QUOTES)
	{
		*token = (*token)->next;
		if (*token && (*token)->type == LITERAL)
			*token = (*token)->next;
	}
}
