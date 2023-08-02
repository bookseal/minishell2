/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gichlee <gichlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 18:19:29 by gichlee           #+#    #+#             */
/*   Updated: 2023/08/02 22:12:02 by gichlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	beg;
	size_t	end;
	size_t	i;
	char	*strtrim;

	if (!s1)
		return (0);
	beg = 0;
	while (s1[beg] != '\0' && ft_strchr(set, s1[beg]))
		beg++;
	end = ft_strlen(s1);
	while (end > beg && ft_strchr(set, s1[end]))
		end--;
	if (beg <= end)
		strtrim = malloc(sizeof(char) * (end - beg + 2));
	else
		strtrim = malloc(sizeof(char));
	if (!strtrim)
		return (0);
	i = 0;
	while (beg <= end)
		strtrim[i++] = s1[beg++];
	strtrim[i] = '\0';
	return (strtrim);
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