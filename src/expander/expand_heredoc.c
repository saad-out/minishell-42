/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 21:13:21 by soutchak          #+#    #+#             */
/*   Updated: 2024/05/03 16:16:28 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/expander.h"
#include "../../inc/memory.h"

static int	is_special(char c)
{
	return (ft_isalnum(c) || c == '_' || c == '&' || c == '|'\
			|| c == '\'', c == '"');
}

char	*join_var_heredoc(char *joined, char *s, int *i)
{
	char	*var;
	char	*tmp;
	int		j;

	var = NULL;
	j = 0;
	var = expand_var(s, &j);
	(*i) += j;
	if (!joined)
		return (var);
	if (var)
	{
		tmp = ft_strjoin(joined, var);
		free(joined);
		free(var);
		return (tmp);
	}
	return (joined);
}

char	*join_regular_heredoc(char *joined, char *s, int *i, const char *set)
{
	char	*tmp;
	char	*tmp2;
	int		j;

	j = 0;
	while (s[j] && !ft_strchr(set, s[j]))
		j++;
	tmp = NULL;
	if (j > 0)
		tmp = ft_strndup(s, j);
	(*i) += j;
	if (!joined)
		return (tmp);
	tmp2 = ft_strjoin(joined, tmp);
	free(joined);
	free(tmp);
	return (tmp2);
}

char	*read_and_expand(int heredoc_fd)
{
	char	*content;
	char	*line;
	int		i;

	content = NULL;
	line = get_next_line(heredoc_fd);
	while (line)
	{
		i = 0;
		while (line[i])
		{
			if (line[i] == '$')
				content = join_var_heredoc(content, line + i, &i);
			else
				content = join_regular_heredoc(content, line + i, &i, "$");
		}
		free(line);
		line = get_next_line(heredoc_fd);
	}
	return (content);
}

void	expand_heredoc(t_redir *redir)
{
	int		heredoc_fd;
	char	*content;
	char	*line;
	int		i;

	if (!redir->expand)
		return ;
	heredoc_fd = open(redir->file, O_RDONLY, 0644);
	if (heredoc_fd == -1)
		return (error("open heredoc", NULL), ft_free_heap(), exit(1));
	content = read_and_expand(heredoc_fd);
	close(heredoc_fd);
	if (content)
	{
		heredoc_fd = open(redir->file, O_WRONLY | O_TRUNC, 0644);
		if (heredoc_fd == -1)
			return (error("open heredoc", NULL), ft_free_heap(), exit(1));
		write(heredoc_fd, content, ft_strlen(content));
		close(heredoc_fd);
		free(content);
	}
}
