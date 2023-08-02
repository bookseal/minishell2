#include "main.h"

int	g_exit_status;

int	null_input_exit(void)
{
	ft_putendl_fd("exit", STDIN);
	return (1);
}

int	loop_prompt(t_env **env_lst)
{
	char	*input;
	t_cmd	*cmds;

	while (1)
	{
		input = readline("minishell $ ");
		if (!input)
			return (null_input_exit());
		if (*input != '\0')
		{
			add_history(input);
			cmds = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
			if (!cmds)
				return (1);
			if (parsing(input, &cmds, env_lst))
				return (1);
		}
		// TODO: execute
		// TODO: exit_status
		free(input);
	}
	return (0);
}

int	set_terminal(void)
{
	struct termios term;

	if (tcgetattr(STDIN_FILENO, &term))
		return (1);
	term.c_lflag &= ~(ECHOCTL);
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term))
		return (1);
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
	// FIXME: SHVLV
	if (envp_to_env_lst(envp, &env_lst))
	{
		env_lstclear(&env_lst, &free);
		return (1);
	}
	// TODO: loop
	if (loop_prompt(&env_lst))
	{
		env_lstclear(&env_lst, &free);
		return (g_exit_status % 255);	
	}
	env_lstclear(&env_lst, &free);
	return (g_exit_status % 255);
}
