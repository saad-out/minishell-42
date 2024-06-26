/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environement.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 18:26:08 by klakbuic          #+#    #+#             */
/*   Updated: 2024/05/11 15:26:54 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/common.h"
#include "../../inc/globals.h"
#include "../../inc/memory.h"

static t_env	*create_env_int(char **key_value)
{
	t_env	*new;

	new = ft_malloc(sizeof(t_env), GENERAL);
	new->key = key_value[0];
	new->value = key_value[1];
	new->visibility = BOTH;
	new->masked = false;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

t_env	*create_env(char *env)
{
	t_env	*new;
	char	**key_value;

	key_value = ft_split(env, "=");
	new = create_env_int(key_value);
	if (ft_strcmp(new->key, "OLDPWD") == 0)
	{
		new->value = NULL;
		new->visibility = EXPORT;
	}
	else if (ft_strcmp(new->key, "SHLVL") == 0)
		set_shelvl(new);
	else if (ft_strcmp(new->key, "_") == 0)
		new->visibility = ENVE;
	else if (ft_strcmp(new->key, "?") == 0)
		new->visibility = SPECIAL;
	return (new);
}

static void	add_empty_env(t_env **envs)
{
	t_env	*new[5];
	char	pwd[PATH_MAX];
	char	*pwd2;
	int		i;

	i = 0;
	getcwd(pwd, PATH_MAX);
	new[0] = create_env("OLDPWD");
	pwd2 = ft_strjoin("PWD=", pwd);
	new[1] = create_env(pwd2);
	new[2] = create_env("SHLVL=0");
	new[3] = create_env("PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin");
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
		add_env(&envs, new);
	}
	return (envs);
}
