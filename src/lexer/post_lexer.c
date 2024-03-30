/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 01:08:57 by klakbuic          #+#    #+#             */
/*   Updated: 2024/03/30 01:36:56 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/common.h"
#include "../../inc/lexer.h"

void print_all_tokens(t_token **tokens)
{
    t_token *head;

    head = *tokens;
    while (head)
    {
        print_token(head);
        head = head->next;
    }
    
}

void	post_lexer(t_token **tokens)
{
	t_token *head;
	t_token *tmp;

	head = *tokens;
	while (head)
	{
		if (head->type == WHITESPACE || head->type == SINGLE_Q || head->type == DOUBLE_Q)
		{
			tmp = head;
			if (!head->prev)
			{
				head = head->next;
				*tokens = head;
				free(tmp);
				continue ;
			}
			else
			{
				head->prev->next = head->next;
				if (head->next)
					head->next->prev = head->prev;
				head = head->next;
				free(tmp);
                continue;
			}
		}
		head = head->next;
	}
}