/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 15:28:10 by klakbuic          #+#    #+#             */
/*   Updated: 2024/05/01 08:34:50 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libs.h"
#include <limits.h>

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		ft_putstr_fd("-2147483648", fd);
		return ;
	}
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n = -n;
	}
	if (n < 10)
	{
		ft_putchar_fd((n % 10) + '0', fd);
		return ;
	}
	ft_putnbr_fd(n / 10, fd);
	ft_putchar_fd((n % 10) + '0', fd);
}
