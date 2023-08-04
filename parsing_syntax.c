/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_syntax.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leegichan <leegichan@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 20:18:01 by gichlee           #+#    #+#             */
/*   Updated: 2023/08/04 11:18:33 by leegichan        ###   ########.fr       */
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
	int	error;
	
	(*cmds)->fd_in = STDIN;
	(*cmds)->fd_out = STDOUT;
	create_argv(*cmds, tokens);
	// test_token_print(*tokens);
	error = 0;
	error = handle_redirection(tokens, *cmds, env_lst);
	if (error)
	{
		// FIXME: error handling
		if (error == 1)
			return (1);
		else if (error == 2)
		{
			print_error(*tokens, "Invalid arguments");
			// g_exit_status = 
		}
		else if (error == 3)
			;
		return (1);
	}
	(*cmds)->built_in = is_built_in((*cmds)->argv[0]);
	if (!(*cmds)->built_in)
	{
		// TODO: test
		if (locate_cmd(*cmds, *env_lst))
		{
			// TODO: error
			return (1);
		}
	}
	// TODO: handle_pipe
	// TODO: exit_status
	return (0);
}