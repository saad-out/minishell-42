/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 01:37:28 by soutchak          #+#    #+#             */
/*   Updated: 2024/05/04 00:13:46 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"
#include "../../inc/memory.h"

char	*read_heardoc(char *delimiter, bool *expand)
{
	static int	heredoc = 1;
	char		*line;
	char		*filename;
	int			fd;
	char		*n;

	delimiter = remove_quotes(delimiter, expand);
	n = ft_itoa(heredoc++);
	filename = ft_strjoin(HEREDOC_FILENAME, n);
	ft_free(n, GENERAL);
	fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
		return (error("open heredoc", NULL), ft_free_heap(), exit(1), NULL);
	line = readline(HEREDOC_PROMPT);
	while (line && ft_strcmp(line, delimiter))
	{
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
		line = readline(HEREDOC_PROMPT);
	}
	close(fd);
	ft_free(delimiter, GENERAL);
	return (filename);
}
