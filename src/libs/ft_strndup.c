/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*           q                                         +:+ +:+
	+:+     */
/*   By: klakbuic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 17:11:12 by klakbuic          #+#    #+#             */
/*   Updated: 2023/11/01 17:54:42 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/common.h"
#include "../../inc/libs.h"
#include "../../inc/memory.h"
#include <stdlib.h>

char	*ft_strndup(const char *str, int n)
{
	char	*nstr;
	int		min;

	min = ft_strlen(str);
	if (n < min)
		min = n;
	nstr = (char *)ft_malloc((min + 1), GENERAL);
	if (!nstr)
		return (NULL);
	ft_memcpy(nstr, str, min);
	nstr[min] = '\0';
	return (nstr);
}
