/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 15:42:36 by soutchak          #+#    #+#             */
/*   Updated: 2024/05/01 19:14:49 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/expander.h"

int	ft_strcmp_lower(const char *s1, const char *s2)
{
	while (*s1 && *s2 && ft_tolower(*s1) == ft_tolower(*s2))
	{
		s1++;
		s2++;
	}
	return ((unsigned char)ft_tolower(*s1) - (unsigned char)ft_tolower(*s2));
}

void	swap(char **a, char **b) {
    char *temp = *a;
    *a = *b;
    *b = temp;
}

void	bubbleSort(char **words, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (ft_strcmp_lower(words[j], words[j + 1]) > 0) {
                swap(&words[j], &words[j + 1]);
            }
        }
    }
}

bool	match(char *pattern, char *candidate, int p, int c, int sp) {
	// for (int i = 0; i < sp; i++)
	// 	printf(" ");
	// printf("===> p[%d]=%c & c[%d]=%c\n", p, pattern[p], c, candidate[c]);
  if (pattern[p] == '\0') {
    return candidate[c] == '\0';
  } else if (pattern[p] == '*') {
    for (; candidate[c] != '\0'; c++) {
      if (match(pattern, candidate, p+1, c, sp + 4))
        return true;
    }
    return match(pattern, candidate, p+1, c, sp + 4);
  } else if (pattern[p] != '?' && pattern[p] != candidate[c]) {
    return false;
  }  else {
    return match(pattern, candidate, p+1, c+1, sp + 4);
  }
}

void	add_filename(char ***argv, int *i, char *s)
{
	char	**new;

	new = malloc(sizeof(char *) * ((*i) + 2));
	if (!new)
		return ; // TODO: malloc failure
	for (int j = 0; j < *i; j++)
		new[j] = (*argv)[j];
	new[*i] = s;
	new[(*i) + 1] = NULL;
	free(*argv);
	*argv = new;
	*i += 1;
}

char	**get_wd_match(char *wd)
{
	DIR				*dir;
	struct dirent	*entry;
	char			**match_dirs;
	int				i;

	dir = opendir(".");
	if (!dir)
	{
		perror("opendir() failed");
		exit(1);
	}
	
	match_dirs = NULL;
	i = 0;
	entry = readdir(dir);
	while (entry)
	{
		if (entry->d_name[0] != '.' && match(wd, entry->d_name, 0, 0, 0))
		{
			add_filename(&match_dirs, &i, ft_strdup(entry->d_name));
			// printf("(%s)\n", entry->d_name);
		}
		entry = readdir(dir);
	}

	// printf("wd BEFORE(%s):\n", wd);
	// for (int j = 0; j < i; j++)
	// 	printf("(%s)\n", match_dirs[j]);
	// printf("\n");
	bubbleSort(match_dirs, i);
	// printf("wd AFTER(%s):\n", wd);
	// for (int j = 0; j < i; j++)
	// 	printf("(%s)\n", match_dirs[j]);
	// printf("\n");

	closedir(dir);
	return (match_dirs);
	// return (NULL);
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
	new = malloc(sizeof(char *) * ((*i) + v_size + 1));
	if (!new)
		return ; // TODO: malloc failure
	j = 0;
	while (j < *i)
	{
		new[j] = (*argv)[j];
		j++;
	}
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

	new_argv = NULL;
	new_argc = 0;
	match = NULL;
	for (int i = 0; i < exec->argc; i++)
	{
		match = get_wd_match(exec->argv[i]);
		if (match)
			add_to_argv_2(&new_argv, &new_argc, match);
		else
			add_filename(&new_argv, &new_argc, exec->argv[i]);
	}
	// free old argv
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
		// ft_putstr_fd("outlaakSH: ", STDERR_FILENO);
		// ft_putstr_fd(redir->file, STDERR_FILENO);
		// ft_putendl_fd(": ambiguous redirect", STDERR_FILENO);
		error(redir->file, "ambiguous redirect");
		free(redir->file);
		redir->file = NULL;
	}
	free(match); // TODO: free all words if more than one word
}

void	expand_wildcards(t_tree *node)
{
	if (node->type == EXEC)
		return (expand_exec_wd((t_exec *)node));
	else
		return (expand_redir_wd((t_redir *)node));
}
