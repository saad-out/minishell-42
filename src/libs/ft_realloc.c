/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 18:15:21 by soutchak          #+#    #+#             */
/*   Updated: 2024/05/04 02:24:31 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/memory.h"
#include <stdlib.h>

void	*ft_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void			*p;
	char			*c;
	char			*k;
	unsigned int	i;

	if (new_size == old_size && ptr)
		return (ptr);
	if (!new_size && ptr)
		return (ft_free(ptr, GENERAL), NULL);
	p = ft_malloc(new_size, GENERAL);
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
	ft_free(ptr, GENERAL);
	return (p);
}
