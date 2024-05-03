/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 02:35:36 by soutchak          #+#    #+#             */
/*   Updated: 2024/05/03 02:36:21 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/expander.h"
#include "../../inc/globals.h"
#include "../../inc/memory.h"

static char	**expand_filenames(t_redir *redir)
{
	int		i;
	bool	split;
	char	*joined;
	char	**words;
	int		size;

	words = NULL;
	size = 0;
	i = 0;
	while (redir->file[i])
	{
		joined = NULL;
		split = 1;
		if (to_expand(redir->file[i]))
		{
			if (redir->file[i] == '\'' || redir->file[i] == '"')
				split = 0;
			joined = join_var(joined, redir->file + i, &i);
		}
		else
			joined = join_regular(joined, redir->file + i, &i, "'\" $");
		if (joined)
			add_to_argv(&words, joined, &size, split);
	}
	return (words);
}

void	expand_redir_vars(t_redir *redir)
{
	int		i;
	bool	split;
	char	*joined;
	char	**words;
	int		size;

	if (redir->type == HEREDOC)
		return (expand_heredoc(redir));
	words = expand_filenames(redir);
	if (!words || count_words(words) != 1)
	{
		error(redir->file, "ambiguous redirect");
		free(redir->file);
		redir->file = NULL;
	}
	else
	{
		free(redir->file);
		redir->file = words[0];
	}
	free(words);
}
