/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 18:15:21 by soutchak          #+#    #+#             */
/*   Updated: 2024/05/02 18:15:59 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/memory.h"
#include <stdlib.h>

void *ft_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *p;
	char *c, *k;
	unsigned int i;

	if (new_size == old_size && ptr)
		return (ptr);
	if (!new_size && ptr)
	{
		free(ptr);
		return (0);
	}
	p = malloc(new_size);
	if (!p)
		return (0);
	if (!ptr)
		return (p);
	i = 0;
	c = p;
	k = ptr;
	while (i < old_size && i < new_size)
	{
		*c++ = *k++;
		i++;
	}
	free(ptr);
	return (p);
}