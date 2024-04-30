/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khalid <khalid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 18:10:02 by klakbuic          #+#    #+#             */
/*   Updated: 2024/04/30 16:05:57 by khalid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/memory.h"

static t_list	**get_heap(t_mem_context context)
{
	static t_list	*heap[ALL + 1];

	return (&heap[context]);
}

static void	del(void *heap_block)
{
	if (heap_block)
		free(heap_block);
}

void	ft_free_heap(void)
{
	int		i;
	t_list	**head;

	i = -1;
	while (++i < ALL)
	{
		head = get_heap((t_mem_context)i);
		ft_lstclear(head, del);
	}
}

void	ft_free(void *heap_block, t_mem_context context)
{
	t_list	**head;
	t_list	*curr;

	head = get_heap(context);
	curr = *head;
	while (curr)
	{
		if (curr->content == heap_block)
		{
			ft_lstdel_node(head, free, curr);
			return ;
		}
		curr = curr->next;
	}
}

void	ft_free_context(t_mem_context context)
{
	t_list	**head;
	t_list	*curr;

	head = get_heap(context);
	curr = *head;
	ft_lstclear(head, del);
}

void	*ft_malloc(size_t size, t_mem_context context)
{
	t_list	**head;
	t_list	*tmp;
	void	*heap_block;

	head = get_heap(context);
	heap_block = malloc(size);
	if (!heap_block)
	{
		ft_free_heap();
		perror("malloc() failure!");
		exit(EXIT_FAILURE);
	}
	tmp = ft_lstnew(heap_block);
	if (!tmp)
	{
		ft_free_heap();
		perror("malloc() failure!");
		exit(EXIT_FAILURE);
	}
	ft_lstadd_back(head, tmp);
	return (heap_block);
}

void	ft_print_mem(t_mem_context context)
{
	t_list **head;
	t_list *curr;

	head = get_heap(context);
	curr = *head;
	while (curr)
	{
		printf("%p\n", curr->content);
		curr = curr->next;
	}
}