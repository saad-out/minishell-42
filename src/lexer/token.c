/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 18:09:05 by klakbuic          #+#    #+#             */
/*   Updated: 2024/05/06 21:39:38 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lexer.h"
#include "../../inc/memory.h"

void	remove_token(t_token **head, t_token *token)
{
	if (!token->prev)
	{
		*head = token->next;
		if (*head)
			(*head)->prev = NULL;
	}
	else
	{
		token->prev->next = token->next;
		if (token->next)
			token->next->prev = token->prev;
	}
	ft_free(token, LEXER);
}

t_token	*new_token(t_etype type, char *s, size_t len)
{
	t_token	*token;

	token = ft_malloc(sizeof(t_token), LEXER);
	token->type = type;
	token->location.start = s;
	token->location.len = len;
	token->prev = NULL;
	token->next = NULL;
	return (token);
}

void	add_token(t_token **head, t_token *token)
{
	t_token	*tmp;

	if (!head)
		return ;
	tmp = *head;
	if (!tmp)
	{
		*head = token;
		return ;
	}
	while (tmp && tmp->next)
		tmp = tmp->next;
	tmp->next = token;
	token->prev = tmp;
}

t_token	*append_new_token(t_token **head, t_etype type, char *s, size_t len)
{
	t_token	*token;

	token = new_token(type, s, len);
	if (!token)
		return (NULL);
	add_token(head, token);
	return (token);
}

void	free_tokens(t_token **token_list)
{
	t_token	*tmp;
	t_token	*next;

	tmp = *token_list;
	while (tmp)
	{
		next = tmp->next;
		ft_free(tmp, LEXER);
		tmp = next;
	}
	*token_list = NULL;
}
