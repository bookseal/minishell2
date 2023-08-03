/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_syntax.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leegichan <leegichan@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 20:18:01 by gichlee           #+#    #+#             */
/*   Updated: 2023/08/03 23:46:55 by leegichan        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	test_token_print(t_token *tokens)
{
	while (tokens)
	{
		printf("value = %s\n", tokens->value);
		printf("tag = %d\n", tokens->tag);
		printf("quotes = %d\n\n", tokens->quote);
		tokens = tokens->next;
	}
}

int	syntax_analyzer(t_cmd **cmds, t_token **tokens, t_env **env_lst)
{
	create_argv(*cmds, tokens);
	test_token_print(*tokens);
	if (handle_redirection(tokens, *cmds, env_lst))
		return (1);
	// TODO: handle_pipe
	// TODO: exit_status
	return (0);
}