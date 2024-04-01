/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 01:37:28 by soutchak          #+#    #+#             */
/*   Updated: 2024/04/01 01:52:22 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

char	*read_heardoc(char *delimiter)
{
	char	*line;
	int		fd;

	fd = open(HEREDOC_FILENAME, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
		return (NULL);
	line = readline(HEREDOC_PROMPT);
	while (line && ft_strcmp(line, delimiter))
	{
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
		line = readline(HEREDOC_PROMPT);
	}
	if (close(fd) == -1)
		return (NULL);
	return (HEREDOC_FILENAME);
}
