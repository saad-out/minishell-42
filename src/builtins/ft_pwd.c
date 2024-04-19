/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:47:57 by klakbuic          #+#    #+#             */
/*   Updated: 2024/04/19 15:07:33 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/common.h"
#define SIZE 1024

int	ft_pwd(t_exec *cmd)
{
	char cwd[SIZE];
	if (getcwd(cwd, SIZE))
		printf("%s\n", cwd);
	else
	{
		perror("getcwd() error");
		return (1);
	}
	return (0);
}