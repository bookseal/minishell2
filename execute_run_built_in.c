#include "main.h"

int	run_built_in(t_cmd *cmd, t_env **env_lst)
{
	// dup_in_and_out(cmd);
	if (cmd->built_in == ECHO_CMD)
		return (built_in_echo(cmd, env_lst));
	else if (cmd->built_in == CD_CMD)
		return (built_in_cd(cmd, env_lst));
	else if (cmd->built_in == PWD_CMD)
		return (built_in_pwd(env_lst));
	else if (cmd->built_in == ENV_CMD)
		return (built_in_env(env_lst));
	else if (cmd->built_in == EXPORT_CMD)
		return (built_in_export(cmd, env_lst));
	// else if (cmd->built_in == UNSET_CMD)
	// 	return (built_in_unset(cmd, env_lst));
	// else if (cmd->built_in == EXIT_CMD)
	// 	return (built_in_exit(cmd, env_lst));
	// dup_and_close(cmd);
	return (0);
}