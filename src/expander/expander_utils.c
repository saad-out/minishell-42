/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 02:32:01 by soutchak          #+#    #+#             */
/*   Updated: 2024/05/04 00:31:09 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/expander.h"
#include "../../inc/globals.h"
#include "../../inc/memory.h"

int	count_words(char **words)
{
	int	len;

	len = 0;
	while (words[len])
		len++;
	return (len);
}

static char	**add_empty_string(char **words, int *size)
{
	char	**tmp;

	tmp = ft_malloc(sizeof(char *) * 2, GENERAL);
	tmp[0] = ft_strdup("");
	tmp[1] = NULL;
	*size = 1;
	ft_free(words, GENERAL);
	return (tmp);
}

static void	add_and_split(char ***argv, char *s, int *argc)
{
	char	**new_av;
	char	**words;
	int		w_size;
	int		i;

	words = ft_split(s, ' ');
	w_size = count_words(words);
	if (w_size == 0)
		words = add_empty_string(words, &w_size);
	new_av = ft_malloc(sizeof(char *) * ((*argc) + w_size + 1), GENERAL);
	i = -1;
	while (++i < (*argc))
		new_av[i] = (*argv)[i];
	i = -1;
	while (++i < w_size)
		new_av[i + (*argc)] = words[i];
	new_av[(*argc) + w_size] = NULL;
	ft_free(words, GENERAL);
	*argc += w_size;
	ft_free(*argv, GENERAL);
	*argv = new_av;
}

static void	add_and_join(char ***argv, char *s, int *argc)
{
	char	**new_av;
	int		i;

	new_av = ft_malloc(sizeof(char *) * ((*argc) + 2), GENERAL);
	i = -1;
	while (++i < (*argc))
		new_av[i] = (*argv)[i];
	new_av[(*argc)] = s;
	new_av[(*argc) + 1] = NULL;
	*argc += 1;
	ft_free(*argv, GENERAL);
	*argv = new_av;
}

void	add_to_argv(char ***argv, char *s, int *argc, bool splt)
{
	if (splt)
		add_and_split(argv, s, argc);
	else
		add_and_join(argv, s, argc);
}
