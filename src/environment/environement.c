/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environement.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 18:26:08 by klakbuic          #+#    #+#             */
/*   Updated: 2024/04/30 08:54:09 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/common.h"

void	print_all_env(t_env *envs, bool env_ex)
{
	while (envs)
	{
		if (envs->masked == 0)
		{
			if (env_ex)
				printf("%s", DECLARE);
			printf("%s", envs->key, envs->value);
			if (envs->value == NULL)
				printf("=\"\"\n");
			else
				printf("=%s\n", envs->value);
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
	if (ft_strcmp(new->key, "?") == 0)
	{
		new->value = key_value[1];
		new->visibility = SPECIAL;
	}
	else if (ft_strcmp(new->key, "OLDPWD") == 0)
	{
		if (key_value[1])
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
	free(key_value);
	return (new);
}

void	add_env(t_env **envs, t_env *new)
{
	t_env	*head;
	int		old_shlvl;

	head = *envs;
	if (!head)
		*envs = new;
	else
	{
		while (head->next)
		{
			if (ft_strcmp(head->key, "SHLVL") == 0)
			{
				if (head->value)
				{
					old_shlvl = ft_atoi(head->value);
					free(head->value);
					head->value = ft_itoa(++old_shlvl);
				}
			}
			head = head->next;
		}
		head->next = new;
		new->prev = head;
	}
}

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

void	add_env_char(t_env **envs, char *key, char *value)
{
	t_env	*head;
	t_env	*new_env;

	new_env = (t_env *)malloc(sizeof(t_env));
	if (!new_env)
	{
		return ;
	}
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
			if (envs->value)
				free(envs->value);
			envs->value = NULL;
			if (new_value)
				envs->value = ft_strdup(new_value);
			envs->masked = false;
			if (new_value == NULL)
				envs->visibility = EXPORT;
			else
				envs->visibility = BOTH;
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
static void	add_empty_env(t_env **envs)
{
	t_env	*new[5];
	char	*pwd;
	char	*PWD;
	int		i;

	i = 0;
	pwd = getcwd(NULL, 1);
	if (pwd == NULL)
	{
		ft_putendl_fd("getcwd() error", STDERR_FILENO);
		exit(1);
	}
	new[0] = create_env("OLDPWD");
	PWD = ft_strjoin("PWD=", pwd);
	new[1] = create_env(PWD);
	free(PWD);
	new[2] = create_env("SHLVL=0");
	new[3] = create_env("PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki");
	new[3]->visibility = SPECIAL;
	new[4] = create_env("_=/usr/bin/env");
	new[4]->visibility = ENVE;
	while (i < 5)
		add_env(envs, new[i++]);
}
t_env	*build_env(char **env)
{
	t_env	*new;
	t_env	*envs;
	int		i;

	envs = NULL;
	i = -1;
	add_env(&envs, create_env("?=0"));
	if (!env[0])
		add_empty_env(&envs);
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

char	**rebuild_env_to_char(t_env *envs)
{
	char	**env;
	int		i;
	t_env	*head;

	head = envs;
	i = 0;
	while (head)
	{
		if (head->masked == 0)
			i++;
		head = head->next;
	}
	env = (char **)malloc(sizeof(char *) * (i + 1));
	if (!env)
		return (NULL); // TODO: handle malloc failure
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
	env[i] = NULL;
	return (env);
}
