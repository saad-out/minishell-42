/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 08:50:04 by klakbuic          #+#    #+#             */
/*   Updated: 2024/05/03 21:24:06 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/common.h"
#include "../../inc/globals.h"
#include "../../inc/memory.h"

bool	exist_key(t_env *envs, const char *key)
{
	while (envs)
	{
		if (ft_strcmp(envs->key, key) == 0)
			return (true);
		envs = envs->next;
	}
	return (false);
}

void	add_env(t_env **envs, t_env *new)
{
	t_env	*head;

	head = *envs;
	if (!head)
		*envs = new;
	else
	{
		while (head->next)
			head = head->next;
		head->next = new;
		new->prev = head;
	}
}

char	**rebuild_env_to_char(t_env *envs)
{
	char	**env;
	int		i;
	t_env	*head;

	head = envs;
	i = 0;
	while (head)
	{
		i = i + (head->masked == 0);
		head = head->next;
	}
	env = (char **)ft_malloc((sizeof(char *) * (i + 1)), GENERAL);
	i = 0;
	head = envs;
	while (head)
	{
		if (head->masked == 0)
		{
			env[i] = ft_strjoin(head->key, "=");
			if (head->value)
				env[i] = ft_strjoin(env[i], head->value);
			i++;
		}
		head = head->next;
	}
	return (env[i] = NULL, env);
}

void	set_nosplt(char **argv, int argc)
{
	if ((argc - 1) != 0)
	{
		set_env(*get_env_list(), "_", argv[argc - 1]);
		return ;
	}
	set_env(*get_env_list(), "_", argv[argc - 1]);
}

void	set_under(char **argv, int argc)
{
	char	**splited;
	int		i;

	i = 0;
	if ((argc - 1) != 0)
	{
		set_env(*get_env_list(), "_", argv[argc - 1]);
		return ;
	}
	splited = ft_split(argv[argc - 1], '/');
	while (splited[i])
		i++;
	if (i == 0)
		i = 1;
	set_env(*get_env_list(), "_", splited[i - 1]);
	ft_free(splited, GENERAL);
}
