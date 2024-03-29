/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 18:09:05 by klakbuic          #+#    #+#             */
/*   Updated: 2024/03/29 01:10:06 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lexer.h"

t_token	*new_token(t_etype type, char *s, size_t len)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
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
	while (tmp && tmp->next)
		tmp = tmp->next;
	if (!tmp)
		*head = token;
	else
	{
		tmp->next = token;
		token->prev = tmp;
	}
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
		// free(tmp->str); // TODO: free only if str is alloc'ed with malloc()
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
	*token_list = NULL;
}

// char	*token_type_to_str(t_etype type)
// {
// 	switch (type)
// 	{
// 	case WORD:
// 		return ("WORD");
// 	case PIPE:
// 		return ("PIPE");
// 	case INPUT:
// 		return ("INPUT");
// 	case OUTPUT:
// 		return ("OUTPUT");
// 	case APPEND:
// 		return ("APPEND");
// 	case HEREDOC:
// 		return ("HEREDOC");
// 	case ENV:
// 		return ("ENV");
// 	case AND:
// 		return ("AND");
// 	case OR:
// 		return ("OR");
// 	case LPAR:
// 		return ("LPAR");
// 	case RPAR:
// 		return ("RPAR");
// 	case UNKNOWN:
// 		return ("UNKNOWN");
// 	case DQUOTE:
// 		return ("DQUOTE");
// 	case SQUOTE:
// 		return ("SQUOTE");
// 	case WILD:
// 		return ("WILD");
// 	case BLOCK:
// 		return ("BLOCK");
// 	case END:
// 		return ("END");
// 	case REDIR:
// 		return ("REDIR");
// 	case CTRL:
// 		return ("CTRL");
// 	case STRING:
// 		return ("STRING");
// 	}
// 	return ("UNKNOWN");
// }