/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_syntax.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gichlee <gichlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 20:18:01 by gichlee           #+#    #+#             */
/*   Updated: 2023/08/02 22:50:47 by gichlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"


int	classify_tags(t_token *tokens)
{
	tags	*tag;
	char	*v;

	while (tokens != 0)
	{
		tag = &(tokens->tag);
		v = tokens->value;
		if (*tag == NEED_DECIDE)
		{
			if (!ft_strncmp(v, ">", 2) || !ft_strncmp(v, ">>", 3))
				*tag = REDIRECTION;
			else if (!ft_strncmp(v, "<", 2) || !ft_strncmp(v, "<<", 3))
				*tag = REDIRECTION;
			else if (ft_strncmp(v, "|", 2) == 0)
				*tag = PIPE;
			else
				return (print_error(tokens, "near unexpected token"));
		}
		tokens = tokens->next;
	}
	return (0);
}

int	syntax_analyzer(t_cmd **cmds, t_token *tokens, t_env **env_lst)
{
	// TODO: test many case
	// if (classify_tags(tokens))
	// {
	// 	token_clear(&tokens, &free);
	// 	return (1);
	// }
	// while (0)
	// {
	// 	// TODO: create argv
	// 	// TODO: handle_redirection
	// 	// TODO: handle_pipe
	// 	// TODO: exit_status
	// }
	// return (0);
}