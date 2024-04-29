/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 19:05:57 by klakbuic          #+#    #+#             */
/*   Updated: 2024/04/29 16:55:20 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/common.h"

static void	ft_swap(t_env *a, t_env *b)
{
	t_env	tmp;

	tmp.key = a->key;
	tmp.value = a->value;
	tmp.visibility = a->visibility;
	tmp.masked = a->masked;
	a->key = b->key;
	a->value = b->value;
	a->visibility = b->visibility;
	a->masked = b->masked;
	b->key = tmp.key;
	b->value = tmp.value;
	b->visibility = tmp.visibility;
	b->masked = tmp.masked;
}

static void	sort_envs(t_env **envs)
{
	int		swapped;
	t_env	*env;

	if (!envs || !*envs)
		return ;
	while (true)
	{
		env = *envs;
		swapped = 0;
		while (env->next)
		{
			if (strcmp(env->key, env->next->key) > 0)
			{
				ft_swap(env, env->next);
				swapped = 1;
			}
			env = env->next;
		}
		if (swapped == 0)
			break ;
	}
}

static void	print_env(t_env *env)
{
	while (env)
	{
		if (env->masked == false && (env->visibility & (BOTH | EXPORT)))
		{
			printf("%s", DECLARE);
			printf("%s", env->key);
			if (env->value != NULL)
				printf("=\"%s\"\n", env->value);
			else
				printf("\n");
		}
		env = env->next;
	}
}

static bool	is_valide_name(char *arg)
{
	int	i;

	i = 0;
	if (!(ft_isalpha(arg[i]) || arg[i] == '_'))
		return (false);
	while (ft_isalpha(arg[i]) || arg[i] == '_')
		i++;
	while (ft_isalpha(arg[i]) || arg[i] == '_' || ft_isdigit(arg[i]))
		i++;
	if (arg[i] == '\0')
		return (true);
	return (false);
}

static void join_env(t_env **envs,char *argv)
{
	char **splited;

	// puts("ana f join");
	splited = ft_split(argv, '=');
	// printf("%p\n", splited[0]);
	if (!is_valide_name(splited[0]))
	{
		// puts("1");
		ft_putstr_fd(argv, STDERR_FILENO);
		ft_putendl_fd(" : not a valid identifier", STDERR_FILENO);
		return ;
	}
	if (argv[ft_strlen(argv) - 1] == '=')
	{
		// puts("3");
		add_env_char(envs, splited[0], "");
	}
	else if (splited[0] && !splited[1])
	{
		// puts("2");
		add_env_char(envs, splited[0], NULL);
	} // TODO: visibility only export
	else
	{
		// puts("4");
		add_env_char(envs, splited[0], splited[1]);
	}
}

int	ft_export(t_exec *cmd)
{
	int i;

	i = 0;
	sort_envs(cmd->env);
	if (cmd->argc == 1)
	{
		print_env(*(cmd->env));
		return (0);
	}
	else
	{
		while (++i < cmd->argc)
		{
			join_env(cmd->env, cmd->argv[i]);
		}
	}
	return (0);
}