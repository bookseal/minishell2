/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_run_built_in.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwonle2 <jiwonle2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 22:30:00 by gichlee           #+#    #+#             */
/*   Updated: 2023/08/14 18:58:28 by jiwonle2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_built_in(t_cmd *cmd, t_env **env_lst)
{
	if (cmd->built_in == ECHO_CMD)
		return (built_in_echo(cmd));
	else if (cmd->built_in == CD_CMD)
		return (built_in_cd(cmd, env_lst));
	else if (cmd->built_in == PWD_CMD)
		return (built_in_pwd(env_lst));
	else if (cmd->built_in == ENV_CMD)
		return (built_in_env(env_lst));
	else if (cmd->built_in == EXPORT_CMD)
		return (built_in_export(cmd, env_lst));
	else if (cmd->built_in == UNSET_CMD)
		return (built_in_unset(cmd, env_lst));
	else if (cmd->built_in == EXIT_CMD)
		return (built_in_exit(cmd, env_lst));
	return (0);
}
