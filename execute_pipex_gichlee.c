#include "main.h"

void	exec_single_cmd(t_cmd *cmd, t_env **env_lst)
{
	t_cmd *cmd1;
	t_cmd *cmd2;
	int	fd_file[2];
	int	fd_pipe[2];

	cmd1 = cmd;
	cmd2 = cmd->next;
	fd_file[0] = cmd1->fd_in;
	fd_pipe[0] = cmd1->pipe_out;
	if (cmd2)
	{
		fd_file[1] = cmd2->fd_out;
		fd_pipe[1] = cmd2->pipe_in;
	}
	close(fd_pipe[0]);
	if (cmd1->built_in)
		run_built_in(cmd1, env_lst);
	else
		execve(cmd1->argv[0], cmd1->argv, 0);
	close(fd_file[0]);
	close(fd_pipe[0]);
	exit(1);
}

void pipex_gichlee(t_cmd *cmds, t_env **env_lst)
{
	int		pid;
	char	**envp;

	if (cmds->built_in)
	{
		pid = fork();
		if (pid == 0)
			exec_single_cmd(cmds, env_lst);
		else
		{
			close_fd(cmds);
			waiting();
		}
	}
	return ;
}