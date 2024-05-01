/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 15:52:35 by soutchak          #+#    #+#             */
/*   Updated: 2024/05/01 09:40:10 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/common.h"
#include "../../inc/libs.h"
#include "../../inc/memory.h"
#include <stdlib.h>
#include <string.h>

static int	ft_count_words(char const *s, char c)
{
	int	words;
	int	i;

	if (!s)
		return (0);
	words = 0;
	i = 0;
	while (s[i] && s[i] == c)
		i++;
	if (!s[i])
		return (0);
	while (s[i])
	{
		if (s[i] != c)
		{
			words++;
			while (s[i] && s[i] != c)
				i++;
		}
		else
			i++;
	}
	return (words);
}

static size_t	ft_strlen_c(char const *s, char c)
{
	size_t	len;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	return (len);
}

static int	ft_strcpy_k(char *dest, char const *src, int c)
{
	int	i;

	i = 0;
	while (src[i] && src[i] != c)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	if (c != '\0')
	{
		while (src[i] == c)
			i++;
	}
	return (i);
}

char	**ft_split(char const *s, char c)
{
	int		words;
	int		i;
	int		k;
	char	**arr;

	words = ft_count_words(s, c);
	arr = (char **)ft_malloc(sizeof(char *) * (words + 1), GENERAL);
	i = 0;
	k = 0;
	while (s && s[k] && s[k] == c)
		k++;
	while (i < words)
	{
		arr[i] = (char *)ft_malloc(sizeof(char) * (ft_strlen_c(s + k, c) + 1), GENERAL);
		k += ft_strcpy_k(arr[i], s + k, c);
		i++;
	}
	arr[i] = 0;
	return (arr);
}