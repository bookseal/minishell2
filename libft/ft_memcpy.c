/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gichlee <gichlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 14:47:00 by gichlee           #+#    #+#             */
/*   Updated: 2022/12/17 14:34:59 by gichlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*char_dst;
	char	*char_src;
	size_t	idx;

	if (dst == 0 && src == 0)
		return (dst);
	char_dst = (char *)dst;
	char_src = (char *)src;
	idx = 0;
	while (idx < n)
	{
		*(char_dst + idx) = *(char_src + idx);
		idx++;
	}
	return (dst);
}
