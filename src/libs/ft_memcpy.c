/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 20:51:15 by klakbuic          #+#    #+#             */
/*   Updated: 2024/05/01 08:34:50 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libs.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	int					i;
	unsigned char		*dst;
	const unsigned char	*sc;

	if (!dest && !src)
		return (dest);
	i = 0;
	dst = dest;
	sc = src;
	if (n != 0)
	{
		while (n-- > 0)
		{
			dst[i] = sc[i];
			i++;
		}
	}
	return (dst);
}
