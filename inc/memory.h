/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 08:33:08 by klakbuic          #+#    #+#             */
/*   Updated: 2024/05/04 01:52:45 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEMORY_H
# define MEMORY_H

# include "common.h"

/*--- TYPES ---*/
typedef struct s_mem	t_mem;
typedef enum e_context	t_mem_context;
/*---       ---*/

/*--- ENUMS ---*/
enum					e_context
{
	LEXER,
	PARSER,
	EXECUTOR,
	EXPANDER,
	GENERAL,
	ALL,
};
/*---       ----*/

/*--- PROTOTYPES ---*/
void				*ft_malloc(size_t size, t_mem_context context);
void				ft_free(void *heap_block, t_mem_context context);
void				ft_free_heap(void);
void				ft_print_mem(t_mem_context context);
void				ft_free_context(t_mem_context context);

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
	struct s_list	*prev;
}					t_list;

t_list				*ft_lstnew(void *content);
bool				ft_lstadd_front(t_list **lst, t_list *new);
bool				ft_lstdel_front(t_list **lst, void (*del)(void *));
bool				ft_lstadd_back(t_list **lst, t_list *new);
bool				ft_lstdel_back(t_list **lst, void (*del)(void *));
bool				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstdel_node(t_list **lst, void (*del)(void *),
						t_list *node);
void				*ft_lstsearh_item(t_list *lst, void *ref, int (*cmp)());
size_t				ft_lstsize(t_list *lst);
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));
bool				ft_lstdel_at_index(t_list **lst, unsigned int index,
						void (*del)(void *));
bool				ft_lstadd_at_index(t_list **lst, t_list *new,
						unsigned int index);
/*---            ---*/

#endif