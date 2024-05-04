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

char	*ft_strdup(const char *str)
{
	char	*nstr;

	nstr = (char *)ft_malloc((ft_strlen(str) + 1), GENERAL);
	if (!nstr)
		return (NULL);
	ft_memcpy(nstr, str, (ft_strlen(str) + 1));
	return (nstr);
}
