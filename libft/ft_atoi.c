/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gichlee <gichlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 19:14:55 by gichlee           #+#    #+#             */
/*   Updated: 2022/12/17 15:59:15 by gichlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*atoa_removed_spaces_sign(char *str, int *sign)
{
	while (*str != '\0')
	{
		if (ft_isdigit(*str))
			break ;
		else if (*str == '+')
		{
			str++;
			break ;
		}
		else if (*str == '-')
		{
			*sign = -1;
			str++;
			break ;
		}
		else if ((9 <= *str && *str <= 13) || *str == ' ')
			str++;
		else
			return (0);
	}
	return (str);
}

int	ft_atoi(const char *str)
{
	char		*num_str;
	int			sign;
	long long	res;

	sign = 1;
	num_str = atoa_removed_spaces_sign((char *)str, &sign);
	if (num_str == 0)
		return (0);
	res = 0;
	while (*num_str != '\0' && ft_isdigit(*num_str))
	{
		res = res * 10 + (*num_str - '0');
		num_str++;
	}
	return ((int)(sign * res));
}
/*
#include <stdio.h>
void	is_ft_atoi_ok(void)
{
	char		*str[50];
	long long	idx;

	str[0] = "0";
	str[1] = "1";
	str[2] = "-1";
	str[3] = "42";
	str[4] = "2147483647";
	str[5] = "-2147483648";
	str[6] = "-2147483696";
	str[7] = "abc-1234";
	str[8] = "-1234abc";
	str[9] = "abc-1234abc";
	str[10] = "\t\t-1234";
	str[11] = "+1234";
	str[12] = "--1234";
	str[13] = "-+1234";
	str[14] = "++1234";
	str[15] = "- 1234";
	str[16] = "+123";
	str[17] = "2147483648";
	str[18] = "-2147483649";
	str[19] = "-999999999999999999999999999999999999999999999999";
	str[20] = "4294967295";
	str[21] = "-4294967296";
	str[22] = "4294967296";
	str[23] = "-4294967297";
	str[24] = "9223372036854775807";
	str[25] = "-9223372036854775808";
	str[26] = "9223372036854775808";
	str[27] = "-9223372036854775809";
	str[28] = "18446744073709551615";
	str[29] = "18446744073709551616";
	str[30] = "-18446744073709551616";
	str[32] = "-18446744073709551617";
	str[33] = "\e12345";
	idx = 0;
	while (idx < 34)
	{
		printf("idx = %lld\n", idx);
		printf("str[idx] = %s\n", str[idx]);
		printf("original_func = %d\n", atoi(str[idx]));
		printf("    your_func = %d\n\n", ft_atoi(str[idx]));
		idx++;
	}
}

int	main(void)
{
	is_ft_atoi_ok();
	return (0);
}
*/