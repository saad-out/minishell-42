/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_iterator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 11:18:49 by klakbuic          #+#    #+#             */
/*   Updated: 2024/03/23 14:44:13 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lexer.h"

bool	itr_has_next(const t_charitr itr)
{
	return (*itr != '\0');
}

char	itr_peek(const t_charitr itr)
{
	return (*itr);
}

char	itr_next(t_charitr *itr)
{
	char	next;

	next = **itr;
	(*itr)++;
	return (next);
}
