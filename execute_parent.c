/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_parent.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwonle2 <jiwonle2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 19:56:21 by jiwonle2          #+#    #+#             */
/*   Updated: 2023/08/13 19:56:22 by jiwonle2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	close_fd(t_cmd *cmds)
{
	t_cmd	*cmd;

	cmd = cmds;
	while (cmd != 0)
	{
		if (cmd->fd_in != 0)
			close(cmd->fd_in);
		if (cmd->fd_out != 1)
			close(cmd->fd_out);
		if (cmd->pipe_in != 0)
			close(cmd->pipe_in);
		if (cmd->pipe_out != 0)
			close(cmd->pipe_out);
		cmd = cmd->next;
	}
}

void	waiting(void)
{
	int	exit_status;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	while (wait(&exit_status) != -1)
	{
		if (WIFSIGNALED(exit_status) != 0)
		{
			ft_putchar_fd('\n', 1);
			g_exit_status = WTERMSIG(exit_status) + 128;
		}
		else if (WIFEXITED(exit_status))
		{
			g_exit_status = WEXITSTATUS(exit_status);
		}
	}
	set_signal();
}
