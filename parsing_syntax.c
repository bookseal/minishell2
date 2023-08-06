/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_syntax.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gichlee <gichlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 20:18:01 by gichlee           #+#    #+#             */
/*   Updated: 2023/08/06 19:53:41 by gichlee          ###   ########.fr       */
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

int	token_to_cmd(t_cmd *cmd, t_token **tokens, t_env **env_lst)
{
	int	error;
	
	cmd->fd_in = STDIN;
	cmd->fd_out = STDOUT;
	create_argv(cmd, tokens);
	error = handle_redirection(tokens, cmd, env_lst);
	if (error)
	{
		if (error == 1)
			return (1);
		else if (error == 2)
			print_error(*tokens, "Invalid arguments");
		else if (error == 3)
			;
		return (1);
	}
	cmd->built_in = is_built_in(cmd->argv[0]);
	if (!cmd->built_in)
	{
		if (locate_cmd(cmd, *env_lst))
			return (1);
	}
	return (error);
}

t_cmd	*new_cmd_for_pipe(t_cmd *cmd, t_token **tokens)
{
	t_cmd	*new_cmd;
	int		fd_pipe[2];
	
	new_cmd = ft_calloc(1, sizeof(t_cmd));
	if (pipe(fd_pipe) == -1)
		exit(1);
	new_cmd->pipe_in = fd_pipe[1];
	cmd->pipe_out = fd_pipe[0];
	cmd->next = new_cmd;
	return (new_cmd);
}

void	make_pipe(t_info *info, int cnt)
{
	int	i;

	i = -1;
	info->fd = malloc(sizeof(int *) * cnt);
	while (++i < cnt)
		info->fd[i] = malloc(sizeof(int) * 2);
	i = -1;
	while (++i < cnt)
	{
		if (pipe(info->fd[i]) < 0)
			exit(1);
	}
}

int	syntax_analyzer(t_cmd **cmds, t_token **tokens, t_env **env_lst, t_info *info)
{
	int		cmd_cnt;
	int		error;
	t_cmd	*cmd;
	
	cmd_cnt = 0;
	cmd = *cmds;
	if (token_to_cmd(cmd, tokens, env_lst))
		return (1);
	while (*tokens && (*tokens)->tag == PIPE)
	{
		(*tokens)->need_to_del = true;
		unnecessary_token_delete(tokens);
		cmd = new_cmd_for_pipe(cmd, tokens);
		cmd_cnt++;
		if (token_to_cmd(cmd, tokens, env_lst))
			return (1);
	}
	make_pipe(info, cmd_cnt);
	// TODO: exit_status
	return (0);
}