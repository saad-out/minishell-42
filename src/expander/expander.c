/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 16:18:37 by soutchak          #+#    #+#             */
/*   Updated: 2024/04/25 18:30:15 by soutchak         ###   ########.fr       */
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
	// printf("===> lets expand VAR from (%s)\n", s);
	j = 0;
	if (*s == '"')
		var = expand_double_q(s, &j);
	else if (*s == '\'')
		var = expand_single_q(s, &j);
	else
		var = expand_var(s, &j);
	(*i) += j;
	// printf("===> DONE (%s) and var (%s)\n", s + j, var);
	if (!joined)
		return (var);
	if (var)
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
	// printf("===> DONE (%s) tmp (%s)\n", s + j, tmp);
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
		return (NULL);
		// return (ft_strdup(""));
		// return (ft_strjoin("$", ft_strndup(var, len)));
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
	// printf("===> lets expand Dq from (%s)\n", s);
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

	// printf("===> lets expand Sq from (%s)\n", s);
	j = 0;
	while (s && !(s[j] == '\''))
		j++;
	(*i) += j + 1;
	return (ft_strndup(s, j));
}

int	count_words(char **words)
{
	int	len;

	len = 0;
	while (words[len])
		len++;
	return (len);
}

char	**add_empty_string(char **words, int *size)
{
	char 	**tmp;

	tmp = malloc(sizeof(char *) * 2);
	if (!tmp)
		return (perror("malloc()"), exit(1), NULL);
	tmp[0] = ft_strdup("");
	tmp[1] = NULL;
	*size = 1;
	free(words);
	return (tmp);
}

void	add_to_argv(char ***argv, char *s, int *argc, bool splt)
{
	int		old_ac;
	char	**old_av;
	// int		new_ac;
	char	**new_av;
	char	**words;
	int		w_size;

	old_ac = *argc;
	old_av = *argv;

	/* split */
	if (splt)
	{
		words = ft_split(s, ' ');
		w_size = count_words(words);
		if (w_size == 0)
			words = add_empty_string(words, &w_size);
	}

	/* copy to new arr */
	if (splt)
		new_av = malloc(sizeof(char *) * (old_ac + w_size + 1));
	else
		new_av = malloc(sizeof(char *) * (old_ac + 2));
	if (!new_av)
		return (perror("malloc()"), exit(1));

	for (int i = 0; i < old_ac; i++)
		new_av[i] = old_av[i];
	if (splt)
	{
		for (int i = 0; i < w_size; i++)
			new_av[i + old_ac] = words[i];
		new_av[old_ac + w_size] = NULL;
		free(words);
		*argc = old_ac + w_size;
	}
	else
	{
		new_av[old_ac] = s;
		new_av[old_ac + 1] = NULL;
		*argc = old_ac + 1;
	}

	/* free old */
	free(old_av);

	*argv = new_av;
}

void	expand_exec_vars(t_exec *exec)
{
	char	**new_argv;
	int		new_argc;
	bool	split;

	new_argv = NULL;
	new_argc = 0;
	for (int i = 0; i < exec->argc; i++)
	{
		char	*joined = NULL;
		int		j = 0;

		while (exec->argv[i][j])
		{
			split = 1;
			if (to_expand(exec->argv[i][j]))
			{
				if (exec->argv[i][j] == '\'' || exec->argv[i][j] == '"')
					split = 0;
				joined = join_var(joined, exec->argv[i] + j, &j);
			}
			else
				joined = join_regular(joined, exec->argv[i] + j, &j, "'\" $");
		}
		// if (joined)
		// 	printf("joined= (%s) & j= (%c)\n", joined, exec->argv[i][j]);
		// else
		// 	printf("joined= (NULL) & j= (%c)\n", exec->argv[i][j]);
		
		if (joined)
			add_to_argv(&new_argv, joined, &new_argc, split);
	}

	exec->argv = new_argv;
	exec->argc = new_argc;
	// printf("\n------ argc -> %d\n", new_argc);
	// for (int i = 0; i < exec->argc; i++)
	// 	printf("argv[%d] = (%s)\n", i, exec->argv[i]);
	// printf("---------\n\n");
}

void	expand_redir_vars(t_redir *redir)
{
	int		i;
	bool	split;
	char	*joined;
	char	**words;
	int		size;

	joined = NULL;
	words = NULL;
	size = 0;
	i = 0;
	while (redir->file[i])
	{
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
	// printf("====> FILE: (%s)\n", joined);


	// for (int i = 0; i < size; i++)
	// 	printf("====> FILE: (%s)\n", words[i]);
	// printf("-------------------\n\n");


	// words = ft_split(joined, ' ');
	if (!words || count_words(words) != 1)
	{
		ft_putstr_fd("outlaakSH: ", STDERR_FILENO);
		ft_putstr_fd(redir->file, STDERR_FILENO);
		ft_putendl_fd(": ambiguous redirect", STDERR_FILENO);
		free(redir->file);
		redir->file = NULL;
	}
	else
	{
		free(redir->file);
		redir->file = words[0];
	}
	free(words); // TODO: free all words if more than one word
}

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
