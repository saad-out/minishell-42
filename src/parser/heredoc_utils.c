/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 19:44:30 by soutchak          #+#    #+#             */
/*   Updated: 2024/05/03 17:05:32 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"
#include "../../inc/memory.h"

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

static char	*join_literal(char *joined, char *del, int *i)
{
	char	*tmp;
	char	*tmp2;

	tmp = get_literal(del, i);
	if (joined)
	{
		tmp2 = ft_strjoin(joined, tmp);
		ft_free(tmp, GENERAL);
		ft_free(joined, GENERAL);
		joined = tmp2;
	}
	else
		joined = tmp;
	return (joined);
}

static char	*join_regular(char *joined, char *del, int *i)
{
	char	*tmp;
	char	*tmp2;

	tmp = get_regular(del, i);
	if (joined)
	{
		tmp2 = ft_strjoin(joined, tmp);
		ft_free(tmp, GENERAL);
		ft_free(joined, GENERAL);
		joined = tmp2;
	}
	else
		joined = tmp;
	return (joined);
}

char	*remove_quotes(char *del, bool *expand)
{
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
			joined = join_literal(joined, del, &i);
		}
		else
			joined = join_regular(joined, del, &i);
	}
	ft_free(del, GENERAL);
	return (joined);
}
