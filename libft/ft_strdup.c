/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gichlee <gichlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 18:33:27 by gichlee           #+#    #+#             */
/*   Updated: 2022/12/03 17:57:44 by gichlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*result_str;
	size_t	len_s1;

	len_s1 = ft_strlen(s1);
	result_str = 0;
	result_str = (char *)malloc(sizeof(char) * (len_s1 + 1));
	if (result_str == 0)
		return (0);
	ft_strlcpy(result_str, s1, len_s1 + 1);
	return (result_str);
}
