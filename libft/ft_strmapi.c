/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gichlee <gichlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 18:40:42 by gichlee           #+#    #+#             */
/*   Updated: 2022/12/05 15:39:14 by gichlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	idx;
	char	*res_str;

	res_str = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (res_str == 0 || f == 0)
		return (0);
	idx = 0;
	while (s[idx] != '\0')
	{
		res_str[idx] = f(idx, s[idx]);
		idx++;
	}
	res_str[idx] = '\0';
	return (res_str);
}
