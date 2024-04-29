/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 08:33:08 by klakbuic          #+#    #+#             */
/*   Updated: 2024/04/29 17:04:29 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEMORY_H
# define MEMORY_H

# include "common.h"

/*--- STRCUTS ---*/
/*---         ---*/

/*--- TYPES ---*/
typedef struct s_mem	t_mem;
typedef enum e_context	t_mem_context;
/*---       ---*/

/*--- STRUCTS ---*/

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
void					*ft_malloc(size_t size, t_mem_context context);
void					ft_free(void *heap_block, t_mem_context context);
void					ft_free_heap(void);
void					ft_print_mem(t_mem_context context);
void					ft_free_context(t_mem_context context);
/*---            ---*/
#endif