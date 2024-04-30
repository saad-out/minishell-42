/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khalid <khalid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 20:57:46 by soutchak          #+#    #+#             */
/*   Updated: 2024/04/30 15:46:55 by khalid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>

# include <stdio.h>

typedef struct s_line {
	char			*block;
	size_t			size;
	struct s_line	*next;
}	t_line;

# ifndef OPEN_MAX
#  define OPEN_MAX 1024
# endif /* OPEN_MAX */

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 50
# endif /* BUFFER_SIZE */

char	*get_next_line(int fd);
void	ft_lstclear2(t_line **line);
char	*ft_strlcpy(char *dest, char *src, size_t dsize);
void	ft_lst_add_back(t_line **line, t_line *node);
t_line	*ft_free_line(t_line **line);
t_line	*ft_adjust_and_free_node(t_line **line, t_line *node, size_t i);

#endif /* GET_NEXT_LINE_BONUS_H */
