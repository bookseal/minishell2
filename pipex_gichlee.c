#include "main.h"

// void	exec_cmd_0(int *fd_file, int *fd_pipe, t_av *av, char **envp)
void	exec_cmd_0(t_cmd *cmd, char **envp, t_env **env_lst)
{
	t_cmd *cmd1;
	t_cmd *cmd2;
	int	fd_file[2];
	int	fd_pipe[2];

	cmd1 = cmd;
	cmd2 = cmd->next;
	fd_file[0] = cmd1->fd_in;
	fd_file[1] = cmd2->fd_out;
	fd_pipe[0] = cmd1->pipe_out;
	fd_pipe[1] = cmd2->pipe_in;

	// close(fd_file[1]);
	close(fd_pipe[0]);
	// dup2(fd_file[0], STDIN_FILENO);
	// close(fd_file[0]);
	dup2(fd_pipe[1], STDOUT_FILENO);
	// close(fd_pipe[1]);
	if (cmd1->built_in)
		run_built_in(cmd1, env_lst);
	else
		execve(cmd1->argv[0], cmd1->argv, envp);
	exit(1);
}

// void	exec_cmd_1(int *fd_file, int *fd_pipe, t_av *av, char **envp)
void	exec_cmd_1(t_cmd *cmd, char **envp, t_env **env_lst)
{
	int	pid;
	t_cmd *cmd1;
	t_cmd *cmd2;
	int	fd_file[3];
	int	fd_pipe[2];

	cmd1 = cmd;
	cmd2 = cmd->next;
	fd_file[0] = cmd1->fd_in;
	fd_file[1] = cmd2->fd_out;
	fd_pipe[0] = cmd1->pipe_out;
	fd_pipe[1] = cmd2->pipe_in;
	
	pid = fd_file[2];
	waitpid(pid, NULL, WNOHANG);
	// close(fd_file[0]);
	close(fd_pipe[1]);
	dup2(fd_pipe[0], STDIN_FILENO);
	close(fd_pipe[0]);
	// dup2(fd_file[1], STDOUT_FILENO);
	// close(fd_file[1]);
	if (cmd2->built_in)
		run_built_in(cmd2, env_lst);
	else
		execve(cmd2->argv[0], cmd2->argv, envp);
	exit(1);
}

void pipex_gichlee(t_cmd *cmds, t_env **env_lst)
{
	int		pid;
	char	**envp;

	// envp = env_lst_to_envp(env_lst);
	
	envp = 0;
	if (cmds->next)
	{
		pid = fork();
		if (pid < 0)
			printf("error");
		else if (pid == 0)
			exec_cmd_0(cmds, envp, env_lst);
		else
			exec_cmd_1(cmds, envp, env_lst);
	}
}