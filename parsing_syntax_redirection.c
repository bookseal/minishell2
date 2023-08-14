/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_syntax_redirection.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gichlee <gichlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 22:22:27 by gichlee           #+#    #+#             */
/*   Updated: 2023/08/14 19:12:11 by gichlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_file(t_token *t, int flag)
{
	int	fd;

	t->need_to_del = TRUE;
	fd = open(t->value, flag, 0644);
	return (fd);
}

int	get_fd_in(t_token *t, t_cmd *cmd)
{
	if (t->tag == REDIRECT_IN)
	{
		cmd->fd_in = open_file(t->next, O_RDONLY);
		if (cmd->fd_in < 0)
			return (openfile_error(t->next->value));
	}
	else if (t->tag == HEREDOC)
		return (handle_heredoc(t->next, cmd));
	return (0);
}

static void	get_fd_out(t_token *t, t_cmd *cmd)
{
	cmd->fd_out = open_file(t->next, O_CREAT | O_WRONLY \
	| O_APPEND);
}

static int	parsing_redirs(t_token **tokens, t_cmd *cmd)
{
	t_token	*t;

	t = *tokens;
	if (t->tag == REDIRECT_OUT)
		cmd->fd_out = open_file(t->next, O_CREAT | O_WRONLY \
		| O_TRUNC);
	else if (t->tag == APPEND_OUT)
		get_fd_out(t, cmd);
	else
		return (get_fd_in(t, cmd));
	return (0);
}

int	handle_redirection(t_token **tokens, t_cmd *cmd)
{
	int	error;

	error = 0;
	while ((*tokens) != 0 && (*tokens)->tag != PIPE && error >= 0)
	{
		(*tokens)->need_to_del = TRUE;
		if ((*tokens)->next != 0 && (*tokens)->next->tag == REDIRECT_INFO)
		{
			error = parsing_redirs(tokens, cmd);
			if (error == 4)
				return (error);
		}
		else
			return (2);
		unnecessary_token_delete(tokens);
	}
	return (error);
}
