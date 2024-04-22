/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 16:18:37 by soutchak          #+#    #+#             */
/*   Updated: 2024/04/22 18:40:15 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/expander.h"

char	*get_var_value(char *var, int len)
{
	char	*key;
	char	*value;

	key = ft_substr(var, 0, len);
	if (!key)
		return (NULL); // handle malloc failure
	value = get_env_value(env_, key);
	if (!value)
		return (NULL);
	return (ft_strdup(value));
}

char	*expand_var(char *var)
{
	int	len;

	// skip $
	var++;

	// get var length
	len = 0;
	while (var[len] && !ft_strchr("'\"$ ", var[len]))
		len++;
	
	// get var value
	return (get_var_value(var, len));
}

void	expand_exec_vars(t_exec *exec)
{
	for (int i = 0; i < exec->argc; i++)
	{
		if (exec->argv[i][0] == '$')
		{
			char	*expanded = expand_var(exec->argv[i]);
			if (expanded)
			{
				printf("====> expanded: %s\n", expanded);
				free(expanded);
				// free(exec->argv[i]);
				// exec->argv[i] = expanded;
			}
			else
				printf("====> not set: %s\n", exec->argv[i]);	
		}
	}
}

void	expand_redir_vars(t_redir *redir)
{}

void	expand_vars(t_tree *node)
{
	if (node->type == EXEC)
		return (expand_exec_vars((t_exec *)node));
	else
		return (expand_redir_vars((t_redir *)node));
}

void	expand_wildcards(t_tree *node)
{}

void	expander(t_tree *node)
{
	printf("expander\n");
	expand_vars(node);
	expand_wildcards(node);
}
