/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 15:52:35 by soutchak          #+#    #+#             */
/*   Updated: 2024/05/07 16:16:17 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/common.h"
#include "../../inc/libs.h"
#include "../../inc/memory.h"
#include <stdlib.h>
#include <string.h>

static int	ft_count_words(char const *s, char *set)
{
	int	words;
	int	i;

	if (!s)
		return (0);
	words = 0;
	i = 0;
	while (s[i] && ft_strchr(set, s[i]))
		i++;
	if (!s[i])
		return (0);
	while (s[i])
	{
		if (!ft_strchr(set, s[i]))
		{
			words++;
			while (s[i] && !ft_strchr(set, s[i]))
				i++;
		}
		else
			i++;
	}
	return (words);
}

static size_t	ft_strlen_c(char const *s, char *set)
{
	size_t	len;

	len = 0;
	while (s[len] && !ft_strchr(set, s[len]))
		len++;
	return (len);
}

static int	ft_strcpy_k(char *dest, char const *src, char *set)
{
	int	i;

	i = 0;
	while (src[i] && !ft_strchr(set, src[i]))
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	while (src[i] && ft_strchr(set, src[i]))
		i++;
	return (i);
}

char	**ft_split(char const *s, char *set)
{
	int		words;
	int		i;
	int		k;
	char	**arr;

	words = ft_count_words(s, set);
	arr = (char **)ft_malloc(sizeof(char *) * (words + 1), GENERAL);
	i = 0;
	k = 0;
	while (s && s[k] && ft_strchr(set, s[k]))
		k++;
	while (i < words)
	{
		arr[i] = (char *)ft_malloc(sizeof(char) * (ft_strlen_c(s + k, set) + 1),
				GENERAL);
		k += ft_strcpy_k(arr[i], s + k, set);
		i++;
	}
	arr[i] = 0;
	return (arr);
}
