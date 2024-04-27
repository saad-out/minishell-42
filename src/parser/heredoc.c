/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 01:37:28 by soutchak          #+#    #+#             */
/*   Updated: 2024/04/27 21:07:44 by soutchak         ###   ########.fr       */
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
	char	*tmp2;
	char	*joined;
	int		i;

	*expand = true;
	i = 0;
	joined = NULL;
	while (del[i])
	{
		if (del[i] == '\'' || del[i] == '\"')
		{
			*expand = false;
			tmp = get_literal(del, &i);
			// printf("====>  tmp: (%s) and del[%d]=%c\n", tmp, i, del[i]);
			if (joined)
			{
				tmp2 = ft_strjoin(joined, tmp);
				free(tmp);
				free(joined);
				joined = tmp2;
			}
			else
				joined = tmp;
		}
		else
		{
			tmp = get_regular(del, &i);
			// printf("====>  tmp: (%s) and del[%d]=%c\n", tmp, i, del[i]);
			if (joined)
			{
				tmp2 = ft_strjoin(joined, tmp);
				free(tmp);
				free(joined);
				joined = tmp2;
			}
			else
				joined = tmp;
		}
		// printf("====> JOINED: (%s)\n", joined);
	}
	free(del);
	return (joined);
}

char	*read_heardoc(char *delimiter, bool *expand)
{
	static int	heredoc = 1;
	char		*line;
	char		*filename;
	int			fd;

	delimiter = remove_quotes(delimiter, expand);
	printf("\t====> dilimiter: (%s)\n\n", delimiter);
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
	free(delimiter);
	return (filename);
}
