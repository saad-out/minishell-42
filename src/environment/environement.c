/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environement.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 18:26:08 by klakbuic          #+#    #+#             */
/*   Updated: 2024/04/18 22:46:45 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/common.h"

void	print_all_env(t_env *envs)
{
	while (envs)
	{
		if (envs->masked == 0)
		{
			// printf("key: %s\n", envs->key);
			// printf("value: %s\n", envs->value);
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

int	env_size(t_env *envs)
{
	int	len;

	len = 0;
	while (envs)
	{
		len++;
		envs = envs->next;
	}
	// printf("envs -> %d\n", len);
	// return (envs);
	return (len);
}

char	**rebuild_env(t_env *envs)
{
	char	**ret_envs;
	int		i;

	int	e_s = env_size(envs);
	ret_envs = malloc(sizeof(char *) * (e_s + 1));
	if (!ret_envs)
		return (NULL); // TODO: handle malloc failure
	i = 0;
	while (envs)
	{
		size_t	key_size = ft_strlen(envs->key);
		size_t	value_size = ft_strlen(envs->value);
		ret_envs[i] = malloc(sizeof(char) * (key_size + value_size + 2));
		if (!ret_envs[i])
			return (NULL); // TODO: handle malloc failure
		ft_memcpy(ret_envs[i], envs->key, key_size);
		ft_memcpy(ret_envs[i] + key_size, "=", 1);
		ft_memcpy(ret_envs[i] + key_size + 1, envs->value, value_size);
		ret_envs[i][key_size + value_size + 1] = '\0';
		i++;
		envs = envs->next;
	}
	ret_envs[i] = NULL;
	return (ret_envs);
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
	return (envs);
}