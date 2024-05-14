/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 19:05:57 by klakbuic          #+#    #+#             */
/*   Updated: 2024/05/11 16:06:21 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/common.h"
#include "../../inc/executor.h"
#include "../../inc/memory.h"

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
	if (!arg)
		return (false);
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

static void	join_value(t_env *envs, char **key, char **value)
{
	char	*key_;
	char	*value_;
	char	*tmp;

	key_ = *key;
	value_ = *value;
	if (!key_ || !value_)
		return ;
	if (key_[ft_strlen(key_) - 1] == '+')
	{
		tmp = key_;
		*key = ft_substr(key_, 0, (ft_strlen(key_) - 1));
		ft_free(tmp, GENERAL);
		if (value_ == NULL)
			return ;
		tmp = value_;
		*value = ft_strjoin(get_env_value(envs, (*key)), value_);
		if (tmp != NULL)
			ft_free(tmp, GENERAL);
		return ;
	}
}

static void	join_env(t_env **envs, char *argv)
{
	char	**splited;

	splited = ft_split(argv, "=");
	if (splited[0])
		join_value((*envs), &splited[0], &splited[1]);
	if (!is_valide_name(splited[0]) || argv[0] == '=')
	{
		ft_putstr_fd(argv, STDERR_FILENO);
		ft_putendl_fd(" : not a valid identifier", STDERR_FILENO);
		return ;
	}
	if (argv[ft_strlen(argv) - 1] == '=')
		add_env_char(envs, splited[0], "");
	else if (splited[0] && !splited[1])
		add_env_char(envs, splited[0], NULL);
	else
		add_env_char(envs, splited[0], splited[1]);
}

int	ft_export(t_exec *cmd)
{
	int	i;

	i = 0;
	sort_envs(cmd->env);
	if (cmd->argc == 1)
	{
		print_env(*(cmd->env));
		return (set_under(cmd->argv, cmd->argc), EXIT_SUCCESS);
	}
	else
		while (++i < cmd->argc)
			join_env(cmd->env, cmd->argv[i]);
	return (set_under(cmd->argv, cmd->argc), EXIT_SUCCESS);
}
