/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gichlee <gichlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 20:09:54 by gichlee           #+#    #+#             */
/*   Updated: 2022/12/04 15:27:41 by gichlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result_s;
	size_t	len_s1;
	size_t	len_s2;

	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	result_s = (char *)malloc(sizeof(char) * (len_s1 + len_s2 + 1));
	if (result_s == 0)
		return (0);
	ft_strlcpy(result_s, s1, len_s1 + 1);
	ft_strlcat(result_s, s2, len_s1 + len_s2 + 1);
	return (result_s);
}
