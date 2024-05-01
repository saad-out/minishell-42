/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 18:47:47 by soutchak          #+#    #+#             */
/*   Updated: 2024/05/01 18:53:16 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void    error(char *word, char *msg)
{
    ft_putstr_fd(RED, STDERR_FILENO);
    ft_putstr_fd(SHELL_ERROR, STDERR_FILENO);
    if (msg)
    {
        ft_putstr_fd(word, STDERR_FILENO);
        ft_putstr_fd(": ", STDERR_FILENO);
        ft_putendl_fd(msg, STDERR_FILENO);
    }
    else
        perror(word);
    ft_putstr_fd(RESET, STDERR_FILENO);
    set_exit_status(EXIT_FAILURE);
}