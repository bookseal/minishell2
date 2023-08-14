/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gichlee <gichlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 21:47:49 by gichlee           #+#    #+#             */
/*   Updated: 2023/08/14 14:33:36 by gichlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	parsing(char *input, t_cmd **cmds, t_env **env_lst, t_info *info)
{
	t_token	*tokens;

	tokens = 0;
	if (lexical_analyzer(&tokens, input, env_lst))
	{
		token_clear(&tokens, &free);
		free(*cmds);
		free(info);
		free(input);
		return (1);
	}
	if (syntax_analyzer(cmds, &tokens, env_lst, info))
	{
		token_clear(&tokens, &free);
		cmds_clear(cmds, &free);
		free(*cmds);
		free(info);
		free(input);
		return (1);
	}
	token_clear(&tokens, &free);
	return (0);
}
