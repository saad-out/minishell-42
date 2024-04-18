/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 01:08:57 by klakbuic          #+#    #+#             */
/*   Updated: 2024/04/18 17:05:16 by klakbuic         ###   ########.fr       */
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

static void remove_quotes(t_token **tokens)
{
	t_token	*current;
	t_token	*tmp;

	current = *tokens;
	while (current)
	{
		if (current->type & QUOTES)
		{
			/* remove first quote*/
			tmp = current->next;
			remove_token(tokens, current);
			current = tmp;

			/* adjust optional literal */
			if (current->type == LITERAL)
			{
				current->location.start--;
				current->location.len += 2;
				current = current->next;
			}

			/* remove second quote */
			tmp = current->next;
			remove_token(tokens, current);
			current = tmp;
		}
		else
			current = current->next;
	}
}

static void	merge_words(t_token **tokens)
{
	t_token	*current;
	t_token	*tmp;

	current = *tokens;
	while (current && current->next)
	{
		if (current->type & STRING && current->next->type & STRING)
		{
			current->location.len += current->next->location.len;
			// tmp = current->next->next;
			tmp = current;
			remove_token(tokens, current->next);
			current = tmp;
		}
		else
			current = current->next;
	}
	return ;
}

static void	remove_whitespaces(t_token **tokens)
{
	t_token	*current;
	t_token	*tmp;

	current = *tokens;
	while (current)
	{
		if (current->type == WHITESPACE)
		{
			tmp = current->next;
			remove_token(tokens, current);
			current = tmp;
		}
		else
			current = current->next;
	}
	return ;
}

void	post_lexer(t_token **tokens)
{
	remove_quotes(tokens);
	print_all_tokens(tokens);
	merge_words(tokens);
	//print_all_tokens(tokens);
	remove_whitespaces(tokens);
}
