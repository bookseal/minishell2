#include "main.h"

int	g_exit_status;

int	loop_readline(t_env **env_lst)
{
	char	*input;
	t_cmd	*cmds;

	while (1)
	{
		input = readline("Minishell $ ");
		if (*input != '\0')
			add_history(input);
		if (parsing(input, &cmds, env_lst))
			return (1);
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

static void	handle_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	handle_sigquit(int sig)
{
	(void)sig;
	rl_redisplay();
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*env_lst;

	(void)argv;
	if (argc != 1)
		return (1);
	if (set_terminal())
		return (1);
	// FIXME: signal
	set_signal();
	if (envp_to_env_lst(envp, &env_lst))
	{
		env_lstclear(&env_lst, &free);
		return (1);
	}
	if (loop_readline(&env_lst))
	{
		env_lstclear(&env_lst, &free);
		return (g_exit_status % 255);	
	}
	env_lstclear(&env_lst, &free);
	return (g_exit_status % 255);
}
