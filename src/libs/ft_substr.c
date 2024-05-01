/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 18:05:29 by klakbuic          #+#    #+#             */
/*   Updated: 2024/05/01 08:46:09 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/common.h"
#include "../../inc/libs.h"
#include "../../inc/memory.h"
#include <stdlib.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*sub;
	unsigned int	i;
	unsigned int	slen;

	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	i = 0;
	if (start > slen)
		len = 0;
	else if (len > slen || (start + len > slen))
		len = slen - start;
	sub = (char *)ft_malloc((len + 1), GENERAL);
	if (!sub)
		return (NULL);
	while (len && len-- > 0)
		sub[i++] = s[start++];
	sub[i] = '\0';
	return (sub);
}
