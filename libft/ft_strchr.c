/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gichlee <gichlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 14:36:10 by gichlee           #+#    #+#             */
/*   Updated: 2022/12/17 15:17:43 by gichlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*ptr_s;
	size_t	idx;	

	ptr_s = (char *)s;
	idx = 0;
	while (1)
	{
		if (ptr_s[idx] == (unsigned char)c)
			return (&ptr_s[idx]);
		else if (ptr_s[idx] == '\0')
			return (0);
		else
			idx++;
	}
	return (0);
}
