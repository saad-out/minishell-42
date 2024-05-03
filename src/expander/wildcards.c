/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 15:42:36 by soutchak          #+#    #+#             */
/*   Updated: 2024/05/03 16:48:40 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/expander.h"
#include "../../inc/memory.h"

void	add_filename(char ***argv, int *i, char *s)
{
	char	**new;
	int		j;

	new = ft_malloc(sizeof(char *) * ((*i) + 2), EXPANDER);
	j = -1;
	while (++j < *i)
		new[j] = (*argv)[j];
	new[*i] = s;
	new[(*i) + 1] = NULL;
	free(*argv);
	*argv = new;
	*i += 1;
}

void	add_to_argv_2(char ***argv, int *i, char **vec)
{
	int		v_size;
	int		j;
	int		k;
	char	**new;

	v_size = 0;
	while (vec[v_size])
		v_size++;
	new = ft_malloc(sizeof(char *) * ((*i) + v_size + 1), EXPANDER);
	j = -1;
	while (++j < *i)
		new[j] = (*argv)[j];
	k = 0;
	while (k < v_size)
		new[j++] = vec[k++];
	new[j] = NULL;
	free(*argv);
	*argv = new;
	*i += (v_size);
}

void	expand_exec_wd(t_exec *exec)
{
	char	**match;
	char	**new_argv;
	int		new_argc;
	int		i;

	new_argv = NULL;
	new_argc = 0;
	match = NULL;
	i = -1;
	while (++i < exec->argc)
	{
		match = get_wd_match(exec->argv[i]);
		if (match)
			add_to_argv_2(&new_argv, &new_argc, match);
		else
			add_filename(&new_argv, &new_argc, exec->argv[i]);
	}
	exec->argc = new_argc;
	exec->argv = new_argv;
}

void	expand_redir_wd(t_redir *redir)
{
	char	**match;

	if (!redir->file)
		return ;
	match = NULL;
	match = get_wd_match(redir->file);
	if (!match)
		return ;
	if (match && match[0] && match[1] == NULL)
	{
		free(redir->file);
		redir->file = match[0];
	}
	else
	{
		error(redir->file, "ambiguous redirect");
		free(redir->file);
		redir->file = NULL;
	}
	free(match);
}

void	expand_wildcards(t_tree *node)
{
	if (node->type == EXEC)
		return (expand_exec_wd((t_exec *)node));
	else
		return (expand_redir_wd((t_redir *)node));
}
