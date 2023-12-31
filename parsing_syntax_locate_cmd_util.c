/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_syntax_locate_cmd_util.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gichlee <gichlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 22:21:42 by gichlee           #+#    #+#             */
/*   Updated: 2023/08/14 19:12:11 by gichlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	strs_free(char **strs)
{
	int	i;

	i = 0;
	if (strs != 0)
	{
		while (strs[i] != 0)
		{
			free(strs[i]);
			i++;
		}
		free(strs);
	}
}

char	*ft_strjoin_with_sep(char const *s1, char const *s2, char *sep)
{
	char	*result_s;
	size_t	len_s1;
	size_t	len_s2;

	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	result_s = (char *)malloc(sizeof(char) * (len_s1 + len_s2 + 2));
	if (result_s == 0)
		return (0);
	ft_strlcpy(result_s, s1, len_s1 + 1);
	ft_strlcat(result_s, sep, len_s1 + 1 + 1);
	ft_strlcat(result_s, s2, len_s1 + 1 + len_s2 + 1);
	return (result_s);
}

void	str_to_lowercase(char *str)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (str[i] != '\0')
	{
		str[i] = ft_tolower(str[i]);
		i++;
	}
}
