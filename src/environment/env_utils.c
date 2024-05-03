/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 08:50:06 by klakbuic          #+#    #+#             */
/*   Updated: 2024/05/03 21:25:00 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/common.h"
#include "../../inc/globals.h"
#include "../../inc/memory.h"

void	print_all_env(t_env *envs)
{
	while (envs)
	{
		if (envs->masked == 0)
		{
			printf("%s", DECLARE);
			printf("%s", envs->key);
			if (envs->value == NULL)
				printf("=\"\"\n");
			else
				printf("=%s\n", envs->value);
		}
		envs = envs->next;
	}
}

void	add_env_char(t_env **envs, char *key, char *value)
{
	t_env	*new_env;

	new_env = (t_env *)ft_malloc(sizeof(t_env), GENERAL);
	new_env->key = key;
	if (value)
		new_env->value = ft_strdup(value);
	else
		new_env->value = NULL;
	new_env->masked = false;
	new_env->visibility = BOTH;
	if (value == NULL)
		new_env->visibility = EXPORT;
	new_env->next = NULL;
	new_env->prev = NULL;
	if (exist_key(*(envs), key))
		set_env(*(envs), key, value);
	else
		add_env(envs, new_env);
}

char	*get_env_value(t_env *envs, const char *key)
{
	while (envs)
	{
		if (ft_strcmp(envs->key, key) == 0 && envs->masked == false)
			return (envs->value);
		envs = envs->next;
	}
	return (NULL);
}

t_env	*get_env(t_env *envs, const char *key)
{
	while (envs)
	{
		if (ft_strcmp(envs->key, key) == 0 && envs->masked == false)
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
			envs->masked = false;
			envs->value = NULL;
			if (envs->visibility != SPECIAL && ft_strcmp(envs->key, "_") != 0)
				envs->visibility = BOTH;
			if (new_value)
				envs->value = ft_strdup(new_value);
			else if (envs->visibility != SPECIAL && ft_strcmp(envs->key, "_") != 0)
				envs->visibility = EXPORT;
			return ;
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
