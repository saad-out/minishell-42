/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 08:30:53 by klakbuic          #+#    #+#             */
/*   Updated: 2024/04/21 08:32:33 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/common.h"

void	split_free(char **splited_str)
{
	int i;

	i = -1;
	if (splited_str == NULL)
		return ;
	while (splited_str[++i] != NULL)
		free(splited_str[i]);
	free(splited_str);
}