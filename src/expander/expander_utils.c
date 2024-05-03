/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 02:32:01 by soutchak          #+#    #+#             */
/*   Updated: 2024/05/03 21:28:28 by soutchak         ###   ########.fr       */
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

	tmp = ft_malloc(sizeof(char *) * 2, EXPANDER);
	tmp[0] = ft_strdup("");
	tmp[1] = NULL;
	*size = 1;
	free(words);
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
	new_av = ft_malloc(sizeof(char *) * ((*argc) + w_size + 1), EXPANDER);
	i = -1;
	while (++i < (*argc))
		new_av[i] = (*argv)[i];
	i = -1;
	while (++i < w_size)
		new_av[i + (*argc)] = words[i];
	new_av[(*argc) + w_size] = NULL;
	free(words);
	*argc += w_size;
	free(*argv);
	*argv = new_av;
}

static void	add_and_join(char ***argv, char *s, int *argc)
{
	char	**new_av;
	int		i;

	new_av = ft_malloc(sizeof(char *) * ((*argc) + 2), EXPANDER);
	i = -1;
	while (++i < (*argc))
		new_av[i] = (*argv)[i];
	new_av[(*argc)] = s;
	new_av[(*argc) + 1] = NULL;
	*argc += 1;
	free(*argv);
	*argv = new_av;
}

void	add_to_argv(char ***argv, char *s, int *argc, bool splt)
{
	if (splt)
		add_and_split(argv, s, argc);
	else
		add_and_join(argv, s, argc);
}
