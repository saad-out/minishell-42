/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:08:12 by klakbuic          #+#    #+#             */
/*   Updated: 2024/04/20 16:13:08 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/common.h"
#include "../../inc/executor.h"


//void	*is_builtin(t_exec *cmd)
int (*is_builtin(char *cmd))(t_exec *exec)
{
	int status_;

	status_ = 0;
	if (ft_strcmp(cmd, "echo") == 0)
		return (ft_echo);
	else if (ft_strcmp(cmd, "pwd") == 0)
		return (ft_pwd);
	else if (ft_strcmp(cmd, "cd") == 0)
		return (ft_cd);
	return (NULL);
}