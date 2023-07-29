/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gichlee <gichlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 19:11:12 by gichlee           #+#    #+#             */
/*   Updated: 2022/11/17 19:11:12 by gichlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	idx;

	if (dstsize < ft_strlen(dst))
		return (ft_strlen(src) + dstsize);
	else
	{
		idx = 0;
		while (dst[idx] != '\0')
			idx++;
		while (idx + 1 < dstsize)
		{
			if (*src != '\0')
				dst[idx] = *src;
			else
				break ;
			src++;
			idx++;
		}
		dst[idx] = '\0';
		return (ft_strlen(src) + ft_strlen(dst));
	}
}
