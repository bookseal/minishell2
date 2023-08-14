/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gichlee <gichlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 21:47:49 by gichlee           #+#    #+#             */
/*   Updated: 2023/08/14 16:58:27 by gichlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	init_cmds_info(char *input, t_cmd **cmds, t_info **info)
{
	add_history(input);
	*cmds = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
	if (!(*cmds))
		return (1);
	*info = (t_info *)ft_calloc(1, sizeof(t_info));
	if (!(*info))
	{
		free(*cmds);
		return (1);
	}
	return (0);
}

int	parsing(char *input, t_cmd **cmds, t_env **env_lst, t_info **info)
{
	t_token	*tokens;
	int		error;

	if (init_cmds_info(input, cmds, info))
		return (1);
	tokens = 0;
	if (lexical_analyzer(&tokens, input, env_lst))
	{
		token_clear(&tokens, &free);
		return (1);
	}
	error = syntax_analyzer(cmds, &tokens, env_lst, *info);
	if (error)
	{
		token_clear(&tokens, &free);
		if (error == 4)
			return (error);
		return (1);
	}
	token_clear(&tokens, &free);
	return (0);
}
