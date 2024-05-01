/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:51:13 by klakbuic          #+#    #+#             */
/*   Updated: 2024/05/01 09:35:03 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lexer.h"
#include "../../inc/common.h"

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
	ft_putstr_fd("eoor", STDERR_FILENO);
	write(STDOUT_FILENO, token->location.start, token->location.len);
	ft_putendl_fd("'", STDERR_FILENO);
}