#include "main.h"

int	g_exit_status;

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
	// TODO: envp_to_env_lst
	if (envp_to_env_lst(envp, &env_lst))
		return (1);
	// TODO: readline_loop
	// TODO: clear_env_lst
	ft_putendl_fd("Hello", 1);
	return (g_exit_status % 255);
}
