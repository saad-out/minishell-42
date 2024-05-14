/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 02:30:12 by soutchak          #+#    #+#             */
/*   Updated: 2024/05/11 16:32:02 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/expander.h"
#include "../../inc/globals.h"
#include "../../inc/memory.h"

bool	to_expand(char c)
{
	return (c == '$' || c == '"' || c == '\'' || c == ' ');
}

static char	*expand_arg(t_exec *exec, int i, bool *split)
{
	char	*joined;
	int		j;

	*split = 1;
	joined = NULL;
	j = 0;
	while (exec->argv[i][j])
	{
		if (to_expand(exec->argv[i][j]))
		{
			if (exec->argv[i][j] == '\'' || exec->argv[i][j] == '"')
				*split = 0;
			joined = join_var(joined, exec->argv[i] + j, &j);
		}
		else
			joined = join_regular(joined, exec->argv[i] + j, &j, "'\"$");
	}
	return (joined);
}

void	expand_exec_vars(t_exec *exec)
{
	char	**new_argv;
	int		new_argc;
	char	*joined;
	bool	split;
	int		i;

	new_argv = NULL;
	new_argc = 0;
	i = 0;
	while (i < exec->argc)
	{
		joined = expand_arg(exec, i, &split);
		if (joined)
			add_to_argv(&new_argv, joined, &new_argc, split);
		i++;
	}
	exec->argv = new_argv;
	exec->argc = new_argc;
}
