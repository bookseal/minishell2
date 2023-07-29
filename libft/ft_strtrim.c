/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gichlee <gichlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 18:19:29 by gichlee           #+#    #+#             */
/*   Updated: 2022/12/18 14:52:00 by gichlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_set(char *set, char c)
{
	size_t	idx;

	idx = 0;
	while (set[idx] != '\0')
	{
		if (set[idx] == c)
			return (1);
		idx++;
	}
	return (0);
}

static size_t	trim_from_end(char *s1, char *set)
{
	size_t	idx;

	idx = ft_strlen(s1) - 1;
	while (idx > 0 && s1[idx] != '\0')
	{
		if (is_set((char *)set, s1[idx]))
			idx--;
		else
			return (idx);
	}
	if (idx == 0)
		return (ft_strlen(s1));
	return (idx);
}

static size_t	trim_from_beginning(char *s1, char *set)
{
	size_t	idx;

	idx = 0;
	while (s1[idx] != '\0')
	{
		if (is_set((char *)set, s1[idx]))
			idx++;
		else
			return (idx);
	}
	return (idx);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*new_str;
	size_t	idx_begin;
	size_t	idx_end;

	if (s1 == 0 || set == 0)
		return (0);
	if (!ft_strlen(s1))
	{
		new_str = (char *)malloc(sizeof(char) * 1);
		*new_str = '\0';
		return (new_str);
	}
	idx_begin = trim_from_beginning((char *)s1, (char *)set);
	idx_end = trim_from_end((char *)s1, (char *)set);
	new_str = (char *)malloc(sizeof(char) * (idx_end - idx_begin + 2));
	if (new_str == 0)
		return (0);
	ft_strlcpy(new_str, &s1[idx_begin], idx_end - idx_begin + 2);
	return (new_str);
}
/*
#include <stdio.h>
void is_ft_strtrim_ok(void)
{
    char    *s1[20];
    char    *set[20];
    int     idx_s1;
    int     idx_set;
	int		len_idx;

    s1[0] = "";
    s1[1] = "a";
    s1[2] = "aa";
    s1[3] = "ab";
    s1[4] = "hello";
	s1[5] = "          ";
	s1[6] = "lorem \n ipsum \t dolor \n  \t amet";
    set[0] = "";
    set[1] = "a";
    set[2] = "aa";
    set[3] = "ab";
    set[4] = "l";
    set[5] = " ";
	set[6] = " ";
	len_idx = 7;
    idx_s1 = 0;
    while (idx_s1 < len_idx)
    {
        printf("s1[idx_s1] = %s\n", s1[idx_s1]);
        idx_set = 0;
        while (idx_set < len_idx)
        {
            printf("set[idx_set] = %s\t", set[idx_set]);
            printf("result = %s\n", ft_strtrim(s1[idx_s1], set[idx_set]));
            idx_set++;
        }
        printf("\n");
        idx_s1++;
    }
}

int main(void)
{
    is_ft_strtrim_ok();
    return (0);
}
*/