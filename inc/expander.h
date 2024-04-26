/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 16:19:03 by soutchak          #+#    #+#             */
/*   Updated: 2024/04/26 16:08:26 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

/* INCLUDES */
# include "common.h"
# include <dirent.h>
/* ------- */

/* PROTOTYPES */
void	expander(t_tree *node);
void	expand_vars(t_tree *node);
/* --------- */

#endif /* EXPANDER_H */
