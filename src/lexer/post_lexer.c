/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 01:08:57 by klakbuic          #+#    #+#             */
/*   Updated: 2024/03/31 00:35:02 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/common.h"
#include "../../inc/lexer.h"

void	print_all_tokens(t_token **tokens)
{
	t_token	*head;

	head = *tokens;
	while (head)
	{
		print_token(head);
		head = head->next;
	}
}

static void	remove_quotes(t_token *token)
{
	size_t	len;
	int		i;
	int		j;
	char	*str;

	len = token->prev->location.len + token->next->location.len;
	i = -1;
	j = 0;
	str = (char *)malloc(sizeof(char) * (len + 1));
	while (++i < (len + 1))
	{
		if (is_quotes(token->prev->location.start[j]))
			j++;
		str[i] = token->prev->location.start[j++];
	}
	str[i] = '\0';
}

static void	remove_token(t_token **tokens, t_token **head, t_token *tmp)
{
	if (!(*head)->prev)
	{
		*head = (*head)->next;
		*tokens = *head;
	}
	else
	{
		(*head)->prev->next = (*head)->next;
		if ((*head)->next)
			(*head)->next->prev = (*head)->prev;
		(*head) = (*head)->next;
	}
	free(tmp);
}

void	post_lexer(t_token **tokens)
{
	t_token	*head;
	t_token	*tmp;

	head = *tokens;
	while (head)
	{
		if (head->type & WHITESPACE || head->type & QUOTES)
		{
			if ((head->type & QUOTES) && head->prev && head->prev->type & WORD)
			{
				if (head->next && (head->next->type & LITERAL))
					remove_quotes(head);
			}
			tmp = head;
			remove_token(tokens, &head, tmp);
			continue ;
		}
		head = head->next;
	}
}
