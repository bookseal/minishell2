/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gichlee <gichlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 19:58:50 by gichlee           #+#    #+#             */
/*   Updated: 2022/12/16 18:40:11 by gichlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char	*ptr_s;
	size_t	idx;

	if (n == 0)
		return (0);
	else
		ptr_s = (char *)s;
	idx = 0;
	while (1)
	{
		if (idx + 1 == n + 1)
			return (0);
		if ((char)(ptr_s[idx]) == (char)c)
			return (&(ptr_s[idx]));
		else
			idx++;
	}
	return (0);
}
