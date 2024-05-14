/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 02:37:30 by soutchak          #+#    #+#             */
/*   Updated: 2024/05/11 16:29:13 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/expander.h"
#include "../../inc/globals.h"
#include "../../inc/memory.h"

char	*join_var(char *joined, char *s, int *i)
{
	char	*var;
	char	*tmp;
	int		j;

	var = NULL;
	j = 0;
	if (*s == '"')
		var = expand_double_q(s, &j);
	else if (*s == '\'')
		var = expand_single_q(s, &j);
	else
		var = expand_var(s, &j);
	(*i) += j;
	if (!joined)
		return (var);
	if (var)
	{
		tmp = ft_strjoin(joined, var);
		ft_free(joined, GENERAL);
		ft_free(var, GENERAL);
		joined = tmp;
	}
	return (joined);
}

char	*join_regular(char *joined, char *s, int *i, const char *set)
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
	ft_free(joined, GENERAL);
	ft_free(tmp, GENERAL);
	return (tmp2);
}

char	*get_var_value(char *var, int len)
{
	char	*key;
	char	*value;

	key = ft_substr(var, 0, len);
	value = get_env_value(*get_env_list(), key);
	if (!value)
		return (NULL);
	return (ft_strdup(value));
}

char	*expand_var(char *var, int *i)
{
	int	len;

	var++;
	(*i)++;
	len = 0;
	if (*var == '?')
	{
		len++;
		(*i) += len;
		return (get_var_value(var, len));
	}
	if (!ft_isalpha(*var) && *var != '_')
		return (ft_strdup("$"));
	len++;
	while (var[len] && (ft_isalnum(var[len]) || var[len] == '_'))
		len++;
	(*i) += len;
	return (get_var_value(var, len));
}
