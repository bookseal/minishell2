/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gichlee <gichlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 19:14:55 by gichlee           #+#    #+#             */
/*   Updated: 2023/08/14 16:40:35 by gichlee          ###   ########.fr       */
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
