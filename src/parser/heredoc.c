/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 01:37:28 by soutchak          #+#    #+#             */
/*   Updated: 2024/05/13 17:39:24 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"
#include "../../inc/memory.h"
#include "../../inc/globals.h"

static void	write_to_heredoc(int fd, char *delimiter)
{
	char		*line;
	int			*error;

	error = heredoc_error();
	line = readline(HEREDOC_PROMPT);
	while (line && ft_strcmp(line, delimiter) && *error == -1)
	{
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
		line = readline(HEREDOC_PROMPT);
		error = heredoc_error();
	}
	if (line)
		free(line);
	if (*error != -1)
	{
		dup2(*error, 0);
		close(*error);
	}
}

char	*read_heardoc(char *delimiter, bool *expand)
{
	static int	heredoc = 1;
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
	signal(SIGINT, heredoc_handler);
	write_to_heredoc(fd, delimiter);
	close(fd);
	ft_free(delimiter, GENERAL);
	ft_init_signals();
	return (filename);
}
