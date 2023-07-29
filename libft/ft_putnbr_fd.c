/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gichlee <gichlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 15:23:17 by gichlee           #+#    #+#             */
/*   Updated: 2022/12/16 21:04:42 by gichlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long long	l_n;
	size_t		chunk;

	l_n = n;
	if (l_n == 0)
	{
		ft_putchar_fd('0', fd);
		return ;
	}
	else if (l_n < 0)
	{
		ft_putchar_fd('-', fd);
		l_n *= -1;
	}
	chunk = 1000000000;
	while (l_n / chunk == 0)
		chunk /= 10;
	while (chunk)
	{
		ft_putchar_fd((l_n / chunk) % 10 + '0', fd);
		chunk /= 10;
	}
}
/*
int	main(void)
{
	ft_putnbr_fd(0, 1);
	return (0);
}
*/
