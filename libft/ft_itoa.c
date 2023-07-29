/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gichlee <gichlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 20:03:01 by gichlee           #+#    #+#             */
/*   Updated: 2022/12/13 16:18:42 by gichlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	assign_digit(char *res_arr, long long *ll_n, long long *chunk)
{
	char	digit;

	while (1)
	{
		if (*chunk == 0)
			break ;
		digit = *ll_n / *chunk;
		*res_arr = digit + '0';
		*ll_n -= digit * (*chunk);
		*chunk /= 10;
		res_arr++;
	}
	*res_arr = '\0';
}

static size_t	n_len(int n, long long *chunk)
{
	size_t	len_n;

	len_n = 1;
	*chunk = len_n;
	while (n / (*chunk))
	{
		len_n++;
		*chunk *= 10;
	}
	len_n--;
	*chunk /= 10;
	return (len_n);
}

static char	*zerotoa(void)
{
	char	*n_arr;

	n_arr = (char *)malloc(sizeof(char) * 2);
	if (n_arr == 0)
		return (0);
	n_arr[0] = '0';
	n_arr[1] = '\0';
	return (n_arr);
}

char	*ft_itoa(int n)
{
	char		*n_arr;
	char		*result_arr;
	size_t		is_neg;
	long long	chunk;
	long long	ll_n;

	is_neg = (n < 0);
	if (n == 0)
		return (zerotoa());
	n_arr = (char *)malloc(sizeof(char) * (n_len(n, &chunk) + is_neg + 1));
	if (n_arr == 0)
		return (0);
	result_arr = n_arr;
	ll_n = n;
	if (is_neg)
	{
		*n_arr = '-';
		n_arr++;
		ll_n *= -1;
	}
	assign_digit(n_arr, &ll_n, &chunk);
	return (result_arr);
}
/*
#include <stdio.h>
void	is_ft_itoa_ok(void)
{
    int    idx;
	printf("%s\n", ft_itoa(-2147483648));
	printf("%s\n", ft_itoa(2147483647));
	printf("%s\n", ft_itoa(10));
    idx = -10;
    while (idx < 101)
    {
        printf("%s\n", ft_itoa(idx));        
        idx++;
    }
}

int main(void)
{
    is_ft_itoa_ok();
    return (0);
}
*/