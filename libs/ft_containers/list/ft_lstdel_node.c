/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel_node.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 18:34:19 by klakbuic          #+#    #+#             */
/*   Updated: 2024/04/28 18:40:23 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lst.h"

void	ft_lstdel_node(t_list **lst, void (*del)(void *), t_list *node)
{
	t_list	*head;

	head = *lst;
	while (head)
	{
		if (head == node)
		{
			if (!head->prev)
			{
				*lst = head->next;
				if (*lst)
					(*lst)->prev = NULL;
			}
			else
			{
				head->prev->next = head->next;
				if (head->next)
					head->next->prev = head->prev;
			}
		}
        del(node->content);
		node->next = NULL;
		node->prev = NULL;
		free(node);
	}
}
