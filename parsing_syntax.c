/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_syntax.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gichlee <gichlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 20:18:01 by gichlee           #+#    #+#             */
/*   Updated: 2023/08/14 16:40:22 by gichlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	handle_error(int error, t_token **tokens, t_env **env_lst)
{
	if (error == 1)
		return (update_exit_status(env_lst, 1));
	else if (error == 2)
	{
		print_error(*tokens, "Invalid arguments");
		return (update_exit_status(env_lst, 2));
	}
	else if (error == 3)
		return (update_exit_status(env_lst, 3));
	else if (error == 4)
		return (error);
	return (update_exit_status(env_lst, 1));
}

int	token_to_cmd(t_cmd *cmd, t_token **tokens, t_env **env_lst)
{
	int	error;

	cmd->fd_in = STDIN;
	cmd->fd_out = STDOUT;
	create_argv(cmd, tokens);
	error = handle_redirection(tokens, cmd);
	if (error)
	{
		error = handle_error(error, tokens, env_lst);
		return (error);
	}
	str_to_lowercase(cmd->argv[0]);
	cmd->built_in = is_built_in(cmd->argv[0]);
	if (!cmd->built_in)
	{
		if (locate_cmd(cmd, *env_lst))
			return (1);
	}
	else
		cmd->is_cmd = 1;
	return (error);
}

t_cmd	*new_cmd_for_pipe(t_cmd *cmd)
{
	t_cmd	*new_cmd;

	new_cmd = ft_calloc(1, sizeof(t_cmd));
	cmd->next = new_cmd;
	return (new_cmd);
}

void	make_pipe(t_info *info, int cnt)
{
	int	i;

	i = -1;
	info->fd = ft_calloc(cnt + 1, sizeof(int *));
	while (++i < cnt)
		info->fd[i] = ft_calloc(2, sizeof(int));
	i = -1;
	while (++i < cnt)
	{
		if (pipe(info->fd[i]) < 0)
			exit(1);
	}
}

int	syntax_analyzer(t_cmd **cmds, t_token **t, t_env **env_lst, t_info *info)
{
	int		cmd_cnt;
	t_cmd	*cmd;
	int		error;

	cmd_cnt = 0;
	cmd = *cmds;
	error = token_to_cmd(cmd, t, env_lst);
	if (error)
		return (error);
	while (*t && (*t)->tag == PIPE)
	{
		(*t)->need_to_del = TRUE;
		unnecessary_token_delete(t);
		cmd = new_cmd_for_pipe(cmd);
		cmd_cnt++;
		error = token_to_cmd(cmd, t, env_lst);
		if (error)
			return (error);
	}
	make_pipe(info, cmd_cnt);
	return (0);
}
