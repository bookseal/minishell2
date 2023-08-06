#include "main.h"

int	g_exit_status;

int	loop_prompt(t_env **env_lst)
{
	char	*input;
	t_cmd	*cmds;
	t_info	*info;

	while (1)
	{
		input = readline("minishell $ ");
		if (!input)
			return (null_input_exit());
		if (*input != '\0')
		{
			add_history(input);
			cmds = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
			info = ft_calloc(1, sizeof(t_info));
			if (!cmds || !info)
				return (1);
			if (parsing(input, &cmds, env_lst, info))
				continue ;
			if (execute(cmds, env_lst, info))
				return (1);
		}
		free(input);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*env_lst;

	(void)argv;
	if (argc != 1)
		return (1);
	if (set_terminal())
		return (1);
	set_signal();
	if (envp_to_env_lst(envp, &env_lst))
	{
		env_lstclear(&env_lst, &free);
		return (1);
	}
	if (loop_prompt(&env_lst))
	{
		env_lstclear(&env_lst, &free);
		return (g_exit_status % 255);
	}
	env_lstclear(&env_lst, &free);
	return (0);
}
