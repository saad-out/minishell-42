/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 02:26:48 by soutchak          #+#    #+#             */
/*   Updated: 2024/05/03 02:28:43 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/expander.h"
#include "../../inc/globals.h"
#include "../../inc/memory.h"

char	*expand_double_q(char *s, int *i)
{
	int		j;
	char	*joined;

	s++;
	(*i)++;
	joined = NULL;
	j = 0;
	while (s && !(s[j] == '"'))
	{
		if (s[j] == '$')
			joined = join_var(joined, s + j, &j);
		else
			joined = join_regular(joined, s + j, &j, "\"$");
	}
	(*i) += j + 1;
	if (!joined)
		return (ft_strdup(""));
	return (joined);
}

char	*expand_single_q(char *s, int *i)
{
	int	j;

	s++;
	(*i)++;
	j = 0;
	while (s && !(s[j] == '\''))
		j++;
	(*i) += j + 1;
	return (ft_strndup(s, j));
}
