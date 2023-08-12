/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_syntax_built_in.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gichlee <gichlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 22:19:33 by gichlee           #+#    #+#             */
/*   Updated: 2023/08/12 22:27:47 by gichlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	is_built_in(char *argv_0)
{
	const char	*b[8] = {"echo", "cd", "pwd", "export", "unset", \
	"env", "exit", 0};
	int			i;

	if (!argv_0)
		return (0);
	i = 0;
	while (b[i])
	{
		if (!ft_strncmp(argv_0, b[i], ft_strlen(b[i]) + 1))
			return (i + 1);
		i++;
	}
	return (0);
}
