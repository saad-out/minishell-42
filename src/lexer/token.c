/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 18:09:05 by klakbuic          #+#    #+#             */
/*   Updated: 2024/05/02 18:57:49 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lexer.h"
#include "../../inc/memory.h"

void	remove_token(t_token **head, t_token *token)
{
	if (!token->prev)
	{
		*head = token->next;
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

char	*token_type_to_str(t_etype type)
{
	switch (type)
	{
		case WORD:
			return ("WORD");
		case PIPE:
			return ("PIPE");
		case APPEND:
			return ("APPEND");
		case HEREDOC:
			return ("HEREDOC");
		case ENV:
			return ("ENV");
		case AND:
			return ("AND");
		case OR:
			return ("OR");
		case LPAR:
			return ("LPAR");
		case RPAR:
			return ("RPAR");
		case UNKNOWN:
			return ("UNKNOWN");
		case REDIR:
			return ("REDIR");
		case CTRL:
			return ("CTRL");
		case STRING:
			return ("STRING");
		case REDIR_IN:
			return ("REDIR_IN");
		case REDIR_OUT:
			return ("REDIR_OUT");
		case WHITESPACE:
			return ("WHITESPACE");
		case SINGLE_Q:
			return ("SINGLE_Q");
		case DOUBLE_Q:
			return ("DOUBLE_Q");
		case WILDCARD:
			return ("WILDCARD");
		case LITERAL:
			return ("LITERAL");
		case BLOCK:
			return ("BLOCK");
		case EXEC:
			return ("EXEC");
	}
	return ("UNKNOWN");
}
