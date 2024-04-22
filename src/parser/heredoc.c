/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 01:37:28 by soutchak          #+#    #+#             */
/*   Updated: 2024/04/01 17:11:19 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

char	*read_heardoc(char *delimiter)
{
	static int	heredoc = 1;
	char		*line;
	char		*filename;
	int			fd;

	filename = ft_strjoin(HEREDOC_FILENAME, ft_itoa(heredoc++));
	fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
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
	return (filename);
}
