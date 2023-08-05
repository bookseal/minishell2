#include "main.h"

void	dup_and_close(t_cmd *cmd)
{
	if (cmd->fd_in != 0)
	{
		close(0);
		dup2(cmd->fd_in_origin, 0);
		close(cmd->fd_in_origin);
	}
	if (cmd->fd_out != 1)
	{
		close(1);
		dup2(cmd->fd_out_origin, 1);
		close(cmd->fd_out_origin);
	}
}

void dup_out(t_cmd *tmp) 
{
	if (tmp->fd_out != 1) 
	{
		tmp->fd_out_origin = dup(1);
		dup2(tmp->fd_out, 1);
		close(tmp->fd_out);
		if (tmp->pipe_out != 0)
			close(tmp->pipe_out);
	} 
	else if (tmp->pipe_out != 0) 
	{
		tmp->fd_out_origin = dup(1);
		dup2(tmp->pipe_out, 1);
		close(tmp->pipe_out);
	}
}

void dup_in(t_cmd *tmp)
{
	if (tmp->fd_in != 0) 
	{
		tmp->fd_in_origin = dup(0);
		dup2(tmp->fd_in, 0);
		close(tmp->fd_in);
		if (tmp->pipe_in != 0)
			close(tmp->pipe_in);
	} 
	else if (tmp->pipe_in != 0) 
	{
		tmp->fd_in_origin = dup(0);
		dup2(tmp->pipe_in, 0);
		close(tmp->pipe_in);
	}
}

void dup_in_and_out(t_cmd *tmp)
{
	dup_in(tmp);
	dup_out(tmp);
}
