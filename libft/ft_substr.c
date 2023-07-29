/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gichlee <gichlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 19:03:32 by gichlee           #+#    #+#             */
/*   Updated: 2022/12/18 14:43:13 by gichlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_malloc_str(char *s, size_t start, size_t len, size_t *size)
{
	char				*result_str;

	if (ft_strlen(s) - start > len)
		*size = len;
	else
		*size = ft_strlen(s) - start;
	result_str = (char *)malloc(sizeof(char) * (*size + 1));
	return (result_str);
}

char	*ft_substr(char const *s, size_t start, size_t len)
{
	char	*result_str;
	size_t	idx;
	size_t	size;

	if (s == 0 || len == 0 || s[0] == '\0' || ft_strlen(s) < start)
	{
		result_str = (char *)malloc(sizeof(char) * 1);
		if (result_str == 0)
			return (0);
		*result_str = '\0';
		return (result_str);
	}
	result_str = ft_malloc_str((char *)s, start, len, &size);
	if (result_str == 0)
		return (0);
	idx = 0;
	while (1)
	{
		if (s[idx] == '\0' || idx == start)
			break ;
		idx++;
	}
	ft_strlcpy(result_str, &s[idx], size + 1);
	return (result_str);
}
