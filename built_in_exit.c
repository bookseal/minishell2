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

// void exit_to_env_lst(t_env *env_lst)
// {
// 	while (env_lst->key != '?')
// 		env_lst = env_lst->next;
// 	if (env_lst->value)
// 		free(env_lst->value);
// 	env_lst->value = ft_strdup("exit");
// }

int built_in_exit(t_cmd *cmd, t_env **env_lst)
{
	int exit_status;

	exit_status = 0;
	if (!cmd->argv[1])
	{	
		ft_putendl_fd("exit", 1);
		// exit_to_env_lst(*env_lst);
		exit(0);
		return (0);
	}
	else if (cmd->argv[2] || !is_valid_argv_1(cmd))
	{
		ft_putendl_fd("exit", 2);
		print_error(NULL, "invalid arguments");
		return (2);
	}
	// exit_status = ft_atoi(cmd->argv[1]);
	ft_putendl_fd("exit", 1);
	// exit_to_env_lst(*env_lst);
	exit(0);
	return (0);
}
