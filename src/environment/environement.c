/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environement.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 18:26:08 by klakbuic          #+#    #+#             */
/*   Updated: 2024/04/20 16:35:36 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/common.h"

void	print_all_env(t_env *envs)
{
	while (envs)
	{
		if (envs->masked == 0)
		{
			printf("%s=%s\n", envs->key, envs->value);
		}
		// printf("visibility: %d\n", envs->visibility);
		envs = envs->next;
	}
	printf("===============================\n\n\n");
}

t_env	*create_env(char *env)
{
	t_env	*new;
	char	**key_value;

	// TODO: handle malloc failure
	key_value = ft_split(env, '=');
	new = malloc(sizeof(t_env));
	new->key = key_value[0];
	if (ft_strcmp(new->key, "OLDPWD") == 0)
	{
		free(key_value[1]);
		new->value = NULL;
		new->visibility = EXPORT;
	}
	else
	{
		new->value = key_value[1];
		new->visibility = BOTH;
	}
	new->masked = false;
	new->prev = NULL;
	new->next = NULL;
	// TODO: free char **key_value
	free(key_value);
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

// void update_env(char *key, char *new_value)
// {
// 	free(env->value);
// 	env->value = new_value;
// }
char	*get_env_value(t_env *envs, const char *key)
{
	while (envs)
	{
		if (ft_strcmp(envs->key, key) == 0)
			return (envs->value);
		envs = envs->next;
	}
	return (NULL);
}

t_env	*get_env(t_env *envs, const char *key)
{
	while (envs)
	{
		if (ft_strcmp(envs->key, key) == 0)
			return (envs);
		envs = envs->next;
	}
	return (NULL);
}

void	set_env(t_env *envs, const char *key, const char *new_value)
{
	while (envs)
	{
		if (ft_strcmp(envs->key, key) == 0)
		{
			free(envs->value);
			// envs->value = new_value;
			envs->value = ft_strdup(new_value);
		}
		envs = envs->next;
	}
}

void	remove_env(t_env **envs, t_env *env)
{
	t_env	*head;

	head = *envs;
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
	// print_all_env(envs);
	return (envs);
}