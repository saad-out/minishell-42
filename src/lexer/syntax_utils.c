/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:51:13 by klakbuic          #+#    #+#             */
/*   Updated: 2024/05/04 02:03:54 by soutchak         ###   ########.fr       */
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

bool	paran_check_nb(t_token **tokens)
{
	t_token	*token;
	int		lparan;
	int		rparan;

	token = *tokens;
	lparan = 0;
	rparan = 0;
	while (token)
	{
		lparan += token->type == LPAR;
		rparan += token->type == RPAR;
		token = token->next;
	}
	lparan += rparan;
	return (!(lparan % 2));
}
