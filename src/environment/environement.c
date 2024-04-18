/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environement.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 18:26:08 by klakbuic          #+#    #+#             */
/*   Updated: 2024/04/18 19:29:08 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/common.h"

void	print_all_env(t_env *envs)
{
	while (envs)
	{
		if (envs->masked == 0)
		{
			printf("key: %s\n", envs->key);
			printf("value: %s\n", envs->value);
		}
		// printf("visibility: %d\n", envs->visibility);
		envs = envs->next;
	}
}

t_env	*create_env(char *env)
{
	t_env	*new;
	char	**key_value;

	// TODO: handle malloc failure
	key_value = ft_split(env, '=');
	new = malloc(sizeof(t_env));
	new->key = key_value[0];
	new->value = key_value[1];
	new->visibility = BOTH;
	new->masked = false;
	new->prev = NULL;
	new->next = NULL;
	// TODO: free char **key_value
	return (new);
}

void	add_env(t_env **envs, t_env *new)
{
	t_env	*head;

	head = *envs;
	if (!head)
		*envs = new;
	else
	{
		// go to the last element of the list
		while (head->next)
			head = head->next;
		head->next = new;
		new->prev = head;
	}
}

char	*get_env(t_env *envs, const char *key)
{
	while (envs)
	{
		if (ft_strcmp(envs->key, key) == 0)
			return (envs->value);
		envs = envs->next;
	}
}

void	remove_env(t_env **envs, t_env *env)
{
	t_env	*head;

	while (head)
	{
		if (head == env)
		{
			env->masked = 1;
			return ;
		}
		head = head->next;
	}
}

t_env	*build_env(char **env)
{
	t_env *new;
	t_env *envs;
	int i;

	envs = NULL;
	i = -1;
	while (env[++i])
	{
		new = create_env(env[i]);
		if (!new)
			return (NULL); // TODO: memory leaks
		add_env(&envs, new);
	}
	print_all_env(envs);
	return (envs);
}