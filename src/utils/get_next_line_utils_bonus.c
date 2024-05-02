/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 23:05:08 by soutchak          #+#    #+#             */
/*   Updated: 2024/05/02 16:27:15 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/get_next_line_bonus.h"
#include "../../inc/memory.h"

void	ft_lstclear2(t_line **line)
{
	t_line	*tmp;
	t_line	*next;

	if (!line || !*line)
		return ;
	tmp = *line;
	next = NULL;
	while (tmp)
	{
		next = tmp->next;
		free(tmp->block);
		free(tmp);
		tmp = next;
	}
	*line = NULL;
	return ;
}

char	*ft_strlcpy(char *dest, char *src, size_t dsize)
{
	size_t	i;

	if (!dest || !src)
		return (dest);
	i = 0;
	while (i < dsize - 1)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

void	ft_lst_add_back(t_line **line, t_line *node)
{
	t_line	*tmp;

	if (!line || !node)
		return ;
	tmp = *line;
	if (!tmp || !tmp->block)
	{
		*line = node;
		return ;
	}
	while (tmp && tmp->next)
		tmp = tmp->next;
	tmp->next = node;
	return ;
}

t_line	*ft_adjust_and_free_node(t_line **line, t_line *node, size_t i)
{
	char	*new_block;

	new_block = (char *)ft_malloc((sizeof(char) * (node->size - i)), GENERAL);
	if (!new_block)
		return (NULL);
	new_block = ft_strlcpy(new_block, node->block + i + 1, node->size - i);
	i = 0;
	while (new_block[i])
		i++;
	node->size = i;
	return (free(node->block), node->block = new_block, *line = node, node);
}

t_line	*ft_free_line(t_line **line)
{
	t_line	*tmp;
	t_line	*next;
	size_t	i;

	tmp = *line;
	while (tmp)
	{
		next = tmp->next;
		i = 0;
		while (tmp->block[i] && tmp->block[i] != '\n')
			i++;
		if (!tmp->block[i])
		{
			free(tmp->block);
			free(tmp);
		}
		else if (tmp->block[i] == '\n')
			return (ft_adjust_and_free_node(line, tmp, i));
		tmp = next;
	}
	return (*line = NULL, NULL);
}
