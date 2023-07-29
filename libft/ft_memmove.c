/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gichlee <gichlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 15:01:57 by gichlee           #+#    #+#             */
/*   Updated: 2022/12/18 15:07:39 by gichlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*char_dst;
	char	*char_src;
	int		idx;

	char_dst = (char *)dst;
	char_src = (char *)src;
	if (char_dst <= char_src)
		return (ft_memcpy(dst, src, len));
	idx = len - 1;
	while (idx >= 0)
	{
		char_dst[idx] = char_src[idx];
		idx--;
	}
	return (dst);
}
