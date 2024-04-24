/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 16:18:37 by soutchak          #+#    #+#             */
/*   Updated: 2024/04/24 22:53:26 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/expander.h"

char	*expand_var(char *var, int *i);
char	*expand_double_q(char *s, int *i);
char	*expand_single_q(char *s, int *i);

static bool	to_expand(char c)
{
	return (c == '$' || c == '"' || c  == '\'' || c == ' ');
}

char	*join_var(char *joined, char *s, int *i)
{
	char	*var;
	int		j;

	var = NULL;
	printf("===> lets expand VAR from (%s)\n", s);
	j = 0;
	if (*s == '"')
		var = expand_double_q(s, &j);
	else if (*s == '\'')
		var = expand_single_q(s, &j);
	else
		var = expand_var(s, &j);
	(*i) += j;
	printf("===> DONE (%s)\n", s + j);
	if (!joined)
		return (var);
	joined = ft_strjoin(joined, var); // free old joined if not NULL
	return (joined);
}

char	*join_regular(char *joined, char *s, int *i, const char *set)
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
	printf("===> DONE (%s)\n", s + j);
	if (!joined)
		return (tmp);
	joined = ft_strjoin(joined, tmp); // free old joined if not NULL
	return (joined);
}

char	*get_var_value(char *var, int len)
{
	char	*key;
	char	*value;

	key = ft_substr(var, 0, len);
	if (!key)
		return (NULL); // handle malloc failure
	value = get_env_value(env_, key);
	if (!value)
		return (ft_strjoin("$", ft_strndup(var, len)));
	return (ft_strdup(value));
}

char	*expand_var(char *var, int *i)
{
	int	len;

	// skip $
	var++;
	(*i)++;

	// get var length
	len = 0;
	while (var[len] && !ft_strchr("'\"$ ", var[len]))
		len++;
	
	(*i) += len;
	
	// get var value
	return (get_var_value(var, len));
}

char	*expand_double_q(char *s, int *i)
{
	int	j;
	char	*joined;

	// skip quote
	s++;
	(*i)++;

	joined = NULL;
	printf("===> lets expand Dq from (%s)\n", s);
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
		return (ft_strndup(s, 0));
	return (joined);
}

char	*expand_single_q(char *s, int *i)
{
	int	j;

	// skip quote
	s++;
	(*i)++;

	printf("===> lets expand Sq from (%s)\n", s);
	j = 0;
	while (s && !(s[j] == '\''))
		j++;
	(*i) += j + 1;
	return (ft_strndup(s, j));
}

void	add_to_argv(char ***argv, char *s, int *argc)
{
	char	**words;
	int		i;
	int		j;

	words = ft_split(s, ' ');
	i = 0;
	while (words[i])
		i++;
	*argv = realloc(*argv, *argc + i);
	j = 0;
	while (*argc < i)
	{
		(*argv)[(*argc)++] = words[j++];
		// printf("====> %d -> (%s)\n", (*argc) - 1, (*argv)[(*argc) - 1]);
	}
}

void	expand_exec_vars(t_exec *exec)
{
	char	**new_argv;
	int		new_argc;

	new_argv = NULL;
	new_argc = 0;
	for (int i = 0; i < exec->argc; i++)
	{
		char	*joined = NULL;
		int		j = 0;

		while (exec->argv[i][j])
		{
			if (to_expand(exec->argv[i][j]))
				joined = join_var(joined, exec->argv[i] + j, &j);
			else
				joined = join_regular(joined, exec->argv[i] + j, &j, "'\" $");
		}
		if (joined)
			printf("joined= (%s) & j= (%c)\n", joined, exec->argv[i][j]);
		else
			printf("joined= (NULL) & j= (%c)\n", exec->argv[i][j]);
		
		add_to_argv(&new_argv, joined, &new_argc);
	}

	// new_argv = realloc(new_argv, new_argc + 1);
	// new_argv[new_argc] = NULL;

	exec->argv = new_argv;
	exec->argc = new_argc;
	for (int i = 0; i < exec->argc; i++)
		printf("argv[%d] = (%s)\n", i, exec->argv[i]);
	printf("---------\n\n");
}

void	expand_redir_vars(t_redir *redir)
{}

void	expand_vars(t_tree *node)
{
	if (node->type == EXEC)
		return (expand_exec_vars((t_exec *)node));
	else
		return (expand_redir_vars((t_redir *)node));
}

void	expand_wildcards(t_tree *node)
{}

void	expander(t_tree *node)
{
	// printf("expander\n");
	expand_vars(node);
	expand_wildcards(node);
}
