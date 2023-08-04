#include "main.h"

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

void signal_handler(int signal_num) {
	if (signal_num == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (signal_num == SIGQUIT)
		rl_redisplay();
}

void set_signal(void)
{
	// cntl + c
	signal(SIGINT, signal_handler);
	// cntl + backslash
	signal(SIGQUIT, signal_handler);
}