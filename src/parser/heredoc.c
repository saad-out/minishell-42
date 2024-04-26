/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 01:37:28 by soutchak          #+#    #+#             */
/*   Updated: 2024/04/26 23:55:51 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

static char	*get_literal(char *del, int *i)
{
	char	*tmp;
	char	c;
	int		j;

	c = del[(*i)++];
	j = *i;
	while (del[j] && del[j] != c)
		j++;
	tmp = ft_substr(del, *i, j - *i);
	*i = j + 1;
	return (tmp);
}

static char	*get_regular(char *del, int *i)
{
	char	*tmp;
	int		j;

	j = *i;
	while (del[j] && del[j] != '\'' && del[j] != '\"')
		j++;
	tmp = ft_substr(del, *i, j - *i);
	*i = j;
	return (tmp);
}

static char	*remove_quotes(char *del, bool *expand)
{
	char	*tmp;
	char	*joined;
	int		i;

	*expand = false;
	i = 0;
	joined = NULL;
	while (del[i])
	{
		if (del[i] == '\'' || del[i] == '\"')
		{
			*expand = true;
			tmp = get_literal(del, &i);
			printf("====>  tmp: (%s) and del[%d]=%c\n", tmp, i, del[i]);
			if (joined)
				ft_strjoin(joined, tmp);
			else
				joined = tmp;
		}
		else
		{
			tmp = get_regular(del, &i);
			printf("====>  tmp: (%s) and del[%d]=%c\n", tmp, i, del[i]);
			if (joined)
				ft_strjoin(joined, tmp);
			else
				joined = tmp;
		}
	}
	free(del);
	return (joined);
}

char	*read_heardoc(char *delimiter)
{
	static int	heredoc = 1;
	char		*line;
	char		*filename;
	int			fd;
	bool		expand;

	delimiter = remove_quotes(delimiter, &expand);
	printf("\t\t====> dilimiter: (%s)\n\n", delimiter);
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
