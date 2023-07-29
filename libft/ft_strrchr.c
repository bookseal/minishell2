/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gichlee <gichlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 19:40:08 by gichlee           #+#    #+#             */
/*   Updated: 2022/12/17 15:20:41 by gichlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*ptr_s;
	size_t	idx;
	char	*ptr_res;

	ptr_res = 0;
	ptr_s = (char *)s;
	idx = 0;
	while (1)
	{
		if (ptr_s[idx] == (unsigned char)c)
			ptr_res = &ptr_s[idx];
		if (ptr_s[idx] == '\0')
			break ;
		else
			idx++;
	}
	return (ptr_res);
}
