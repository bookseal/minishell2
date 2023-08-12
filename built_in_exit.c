#include "main.h"

int is_valid_argv_1(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (i < ft_strlen(cmd->argv[1]))
	{
		if (!ft_isdigit(cmd->argv[1][i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

void exit_to_env_lst(t_env *env_lst, int *exit_status)
{
	while (env_lst->tag != ENV_EXIT)
		env_lst = env_lst->next;
	if (env_lst->value)
		free(env_lst->value);
	env_lst->value = ft_strdup("exit");
	if (exit_status)
		env_lst->exit_status = *exit_status;
	// printf("env_lst->exit_status = %d\n", env_lst->exit_status);
}

int built_in_exit(t_cmd *cmd, t_env **env_lst)
{
	if (!cmd->argv[1])
	{	
		ft_putendl_fd("exit", 1);
		exit_to_env_lst(*env_lst, 0);
		return (-1);
	}
	else if (cmd->argv[2] || !is_valid_argv_1(cmd))
	{
		ft_putendl_fd("exit", 2);
		print_error(NULL, "invalid arguments");
		return (-1);
	}
	// exit_status = ft_atoi(cmd->argv[1]);
	g_exit_status = ft_atoi(cmd->argv[1]);
	// printf("built_in_exit : g_exit_status = %d\n", g_exit_status);
	ft_putendl_fd("exit", 1);
	exit_to_env_lst(*env_lst, &g_exit_status);
	return (g_exit_status);
}
// FIXME: exit when -1

