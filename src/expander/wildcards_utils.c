/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:47:35 by soutchak          #+#    #+#             */
/*   Updated: 2024/05/03 16:49:36 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/expander.h"
#include "../../inc/memory.h"

static void	swap(char **a, char **b)
{
	char	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

static void	bubble_sort(char **words, int n)
{
	int	i;
	int	j;

	i = 0;
	while (i < n - 1)
	{
		j = 0;
		while (j < n - i - 1)
		{
			if (ft_strcmp(words[j], words[j + 1]) > 0)
				swap(&words[j], &words[j + 1]);
			j++;
		}
		i++;
	}
}

bool	match(char *pattern, char *candidate, int p, int c)
{
	if (pattern[p] == '\0')
		return (candidate[c] == '\0');
	else if (pattern[p] == '*')
	{
		while (candidate[c] != '\0')
		{
			if (match(pattern, candidate, p + 1, c))
				return (true);
			c++;
		}
		return (match(pattern, candidate, p + 1, c));
	}
	else if (pattern[p] != '?' && pattern[p] != candidate[c])
		return (false);
	else
		return (match(pattern, candidate, p + 1, c + 1));
}

char	**get_wd_match(char *wd)
{
	DIR				*dir;
	struct dirent	*entry;
	char			**match_dirs;
	int				i;

	dir = opendir(".");
	if (!dir)
		return (error("opendir() failed", NULL), exit(1), NULL);
	match_dirs = NULL;
	i = 0;
	entry = readdir(dir);
	while (entry)
	{
		if (entry->d_name[0] != '.' && match(wd, entry->d_name, 0, 0))
			add_filename(&match_dirs, &i, ft_strdup(entry->d_name));
		entry = readdir(dir);
	}
	bubble_sort(match_dirs, i);
	closedir(dir);
	return (match_dirs);
}
