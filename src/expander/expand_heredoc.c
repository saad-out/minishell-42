/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 21:13:21 by soutchak          #+#    #+#             */
/*   Updated: 2024/05/01 16:09:51 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/expander.h"

static int	is_special(char c)
{
	return (ft_isalnum(c) || c == '_' || c == '&' || c == '|'\
			|| c == '\'', c == '"');
}

char	*join_var_heredoc(char *joined, char *s, int *i)
{
	char	*var;
	int		j;

	var = NULL;
	// printf("===> lets expand VAR from (%s)\n", s);
	j = 0;
	var = expand_var(s, &j);
	(*i) += j;
	// printf("===> DONE (%s) and var (%s)\n", s + j, var);
	if (!joined)
		return (var);
	// printf("====> j: (%s) & var: (%s) ", joined, var);
	if (var)
		joined = ft_strjoin(joined, var); // free old joined if not NULL
	// printf("=%s\n", joined);
	return (joined);
}

char	*join_regular_heredoc(char *joined, char *s, int *i, const char *set)
{
	char	*tmp;
	int		j;

	j = 0;
	// while (s[j] && !to_expand(s[j]))
	while (s[j] && !ft_strchr(set, s[j]))
		j++;
	tmp = NULL;
	if (j > 0)
		tmp = ft_strndup(s, j);
	(*i) += j;
	// printf("===> DONE (%s) tmp (%s)\n", s + j, tmp);
	if (!joined)
		return (tmp);
	joined = ft_strjoin(joined, tmp); // free old joined if not NULL
	return (joined);
}

void	expand_heredoc(t_redir *redir)
{
	int		heredoc_fd;
	char	*content;
	char	*line;
	int		i;

	if (!redir->expand)
		return ;
	/* open heredoc file for reading */
	heredoc_fd = open(redir->file, O_RDONLY, 0644);
	if (heredoc_fd == -1)
		return ; // handle error
	content = NULL;
	line = get_next_line(heredoc_fd);
	while (line)
	{
		i = 0;
		// printf("\t==>line: (%s)\n", line);
		// sleep(1);
		while (line[i])
		{
			if (line[i] == '$')
				content = join_var_heredoc(content, line + i, &i);
			else
				content = join_regular_heredoc(content, line + i, &i, "$");
			// printf("\t==>content; (%s) and line=(%s)\n", content, line + i);
			// sleep(1);
		}
		free(line);
		line = get_next_line(heredoc_fd);
	}
	// printf("FILE:\n(%s)\n", content);
	close(heredoc_fd);

	/* open file for writing */
	if (content)
	{
		heredoc_fd = open(redir->file, O_WRONLY | O_TRUNC, 0644);
		if (heredoc_fd == -1)
			return ; // handle error
		write(heredoc_fd, content, ft_strlen(content));
		close(heredoc_fd);
		free(content);
	}
}
