/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 20:36:18 by klakbuic          #+#    #+#             */
/*   Updated: 2024/05/01 08:44:35 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/common.h"
#include "../../inc/libs.h"
#include "../../inc/memory.h"
#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	len1;
	size_t	len2;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	len1 = 0;
	len2 = 0;
	if (s1)
		len1 = ft_strlen(s1);
	if (s2)
		len2 = ft_strlen(s2);
	str = (char *)ft_malloc((len1 + len2 + 1), GENERAL);
	if (!str)
		return (NULL);
	ft_memcpy(str, s1, len1);
	ft_memcpy((str + len1), s2, len2);
	str[len1 + len2] = '\0';
	return (str);
}