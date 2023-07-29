/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gichlee <gichlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 21:10:15 by gichlee           #+#    #+#             */
/*   Updated: 2022/12/03 15:02:10 by gichlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	ch1;
	unsigned char	ch2;
	size_t			idx;

	if (n == 0)
		return (0);
	idx = 0;
	while (1)
	{		
		ch1 = (unsigned char)s1[idx];
		ch2 = (unsigned char)s2[idx];
		if (ch1 != ch2 || ch1 == '\0' || ch2 == '\0' || idx + 1 == n)
			break ;
		idx++;
	}
	return (ch1 - ch2);
}
