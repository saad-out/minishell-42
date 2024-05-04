/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 02:18:37 by soutchak          #+#    #+#             */
/*   Updated: 2024/05/04 02:18:38 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/memory.h"

bool	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*curr;
	t_list	*head;

	if (del == NULL || lst == NULL || *lst == NULL)
		return (false);
	head = *lst;
	curr = head;
	while (head != NULL)
	{
		head = head->next;
		del(curr->content);
		curr->next = NULL;
		curr->prev = NULL;
		free(curr);
		curr = head;
	}
	*lst = NULL;
	return (true);
}

static t_list	*ft_lstlast(t_list *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

bool	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (new == NULL || lst == NULL)
		return (false);
	if (*lst == NULL)
	{
		*lst = new;
		return (true);
	}
	last = ft_lstlast(*lst);
	last->next = new;
	new->prev = last;
	return (true);
}

t_list	*ft_lstnew(void *content)
{
	t_list	*newnode;

	newnode = (t_list *)malloc(sizeof(t_list));
	if (newnode == NULL)
		return (NULL);
	newnode->content = content;
	newnode->prev = NULL;
	newnode->next = NULL;
	return (newnode);
}

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
			del(node->content);
			free(node);
			return ;
		}
		head = head->next;
	}
}
