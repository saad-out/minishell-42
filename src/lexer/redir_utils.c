/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 09:45:47 by klakbuic          #+#    #+#             */
/*   Updated: 2024/05/01 09:47:43 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lexer.h"

t_token	*greater_append(t_charitr *itr)
{
	t_token	*token;

	token = new_token(UNKNOWN, *itr, 0);
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

t_token	*less_heredoc(t_charitr *itr)
{
	t_token	*token;

	token = new_token(UNKNOWN, *itr, 0);
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
