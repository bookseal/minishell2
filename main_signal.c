#include "main.h"

void signal_handler(int signal_num) {
	if (signal_num == SIGINT)
	{
		ft_putendl_fd("", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (signal_num == SIGQUIT)
	{
		;
	}
	if (signal_num == SIGTERM)
	{
		ft_putstr_fd("\033[1A", 1); // cursor up
		ft_putstr_fd("\033[10C", 1); // cursor 10 forward
		ft_putstr_fd(" exit\n", 1);
		exit(-1);
	}
}

void set_signal(void)
{
	// cntl + c
	signal(SIGINT, signal_handler);
	// cntl + d
	signal(SIGQUIT, SIG_IGN);
	// cntl + /
	signal(SIGTERM, signal_handler);
}