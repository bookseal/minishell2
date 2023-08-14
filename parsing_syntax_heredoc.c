/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_syntax_heredoc.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gichlee <gichlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 22:21:14 by gichlee           #+#    #+#             */
/*   Updated: 2023/08/14 16:09:35 by gichlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	signal_handler_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		exit(1);
	}
}

void	loop_heredoc(char *end, int fd)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strncmp(line, end, ft_strlen(end) + 1) == 0)
			break ;
		ft_putstr_fd(line, fd);
		ft_putstr_fd("\n", fd);
		free(line);
	}
	if (line != 0)
		free(line);
}

static void	open_heredoc(char *end, int *fd_pipe)
{
	signal(SIGINT, signal_handler_heredoc);
	close(fd_pipe[0]);
	loop_heredoc(end, fd_pipe[1]);
	close(fd_pipe[1]);
}

static int	dup_heredoc(t_cmd *cmd, int *fd_pipe)
{
	int	exit_status;

	signal(SIGINT, SIG_IGN);
	wait(&exit_status);
	close(fd_pipe[1]);
	if (WIFEXITED(exit_status))
	{
		exit_status = WEXITSTATUS(exit_status);
		if (exit_status == 1)
			return (-3);
		else
			cmd->fd_in = dup(fd_pipe[0]);
		close(fd_pipe[0]);
	}
	if (set_terminal())
		return (1);
	set_signal();
	return (0);
}

int	handle_heredoc(t_token *token, t_cmd *cmd)
{
	int	pid;
	int	fd_pipe[2];
	int	i;

	token->need_to_del = TRUE;
	i = pipe(fd_pipe);
	if (i == -1)
		exit(1);
	pid = fork();
	if (pid == 0)
	{
		open_heredoc(token->value, fd_pipe);
		return (4);
	}
	else
		dup_heredoc(cmd, fd_pipe);
	return (0);
}
