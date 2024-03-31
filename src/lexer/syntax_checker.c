/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 00:40:16 by klakbuic          #+#    #+#             */
/*   Updated: 2024/03/31 00:53:19 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lexer.h"

static bool	quotes_checker(t_token **tokens)
{
	t_token	*head;
	int		nb_single_q;
	int		nb_double_q;

	head = *tokens;
	nb_single_q = 0;
	nb_double_q = 0;
	while (head)
	{
		if (head->type == SINGLE_Q)
			nb_single_q++;
		if (head->type == DOUBLE_Q)
			nb_double_q++;
		head = head->next;
	}
	if (nb_single_q % 2 || nb_double_q % 2)
		return (true);
	return (false);
}

void	syntax_checker(t_token **tokens)
{
	if (quotes_checker(tokens))
	{
		printf("Unclosed strings\n");
	}
}