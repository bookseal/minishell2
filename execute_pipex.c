/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwonle2 <jiwonle2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 22:06:47 by gichlee           #+#    #+#             */
/*   Updated: 2023/08/13 19:46:17 by jiwonle2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	pipex(t_cmd *cmd, t_env **env_lst, t_info *info)
{
	t_cmd	*tmp;

	info->cmd_cnt = 0;
	tmp = cmd;
	while (tmp)
	{
		if (tmp->is_cmd)
			info->cmd_cnt++;
		else
		{
			if (!tmp->is_cmd && !tmp->next)
			{
				g_exit_status = 127;
				return ;
			}
		}
		tmp = tmp->next;
	}
	if (cmd->built_in && info->cmd_cnt == 1 && cmd->fd_out == 1)
		run_built_in(cmd, env_lst);
	else
		make_process(cmd, info, env_lst, -1);
}

void	make_process(t_cmd *cmd, t_info *info, t_env **env_lst, int i)
{
	pid_t	pid;
	t_cmd	*tmp;
	int		exit_status;

	tmp = cmd;
	while (++i < info->cmd_cnt)
	{
		if (i != 0)
			tmp = tmp->next;
		pid = fork();
		if (!tmp->is_cmd)
		{
			while (!tmp->is_cmd)
				tmp = tmp->next;
		}
		if (pid == 0)
			execute_cmd(tmp, info, env_lst, i);
	}
	close_fds(info);
	i = -1;
	while (++i < info->cmd_cnt)
		wait(&exit_status);
	g_exit_status = WEXITSTATUS(exit_status);
	update_exit_status(env_lst, g_exit_status);
}

void	execute_cmd(t_cmd *cmd, t_info *info, t_env **env_lst, int idx)
{
	char	**envp;

	env_lst_to_envp(*env_lst, &envp);
	if (idx == 0)
	{	
		dup2(cmd->fd_in, STDIN_FILENO);
		if (info->cmd_cnt == 1)
			dup2(cmd->fd_out, STDOUT_FILENO);
		else
			dup2(info->fd[idx][1], STDOUT_FILENO);
	}
	else if (idx == info->cmd_cnt - 1)
	{
		dup2(info->fd[idx - 1][0], STDIN_FILENO);
		dup2(cmd->fd_out, STDOUT_FILENO);
	}
	else
	{
		dup2(info->fd[idx - 1][0], STDIN_FILENO);
		dup2(info->fd[idx][1], STDOUT_FILENO);
	}
	close_fds(info);
	if (cmd->built_in)
		exit(run_built_in(cmd, env_lst));
	execve(cmd->argv[0], cmd->argv, envp);
}

void	close_fds(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->cmd_cnt - 1)
	{
		close(info->fd[i][0]);
		close(info->fd[i][1]);
	}
}
