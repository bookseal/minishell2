#include "main.h"

void signal_handler(int signal_num) {
	// if (signal_num == SIGINT)
	// {
	// 	write(1, "\n", 1);
	// 	rl_on_new_line();
	// 	rl_replace_line("", 0);
	// 	rl_redisplay();
	// }
	// if (signal_num == SIGQUIT)
	// {
	// 	printf("\033[1A"); // cursor up
	// 	printf("\033[10C"); // cursor 10 forward
	// 	printf(" exit\n");
	// 	exit(-1);
	// }
}

void set_signal(void)
{
	// TODO: test
	// cntl + c
	// signal(SIGINT, signal_handler);
	// // cntl + d
	// signal(SIGQUIT, signal_handler);
	// // cntl + /
	// signal(SIGTERM, signal_handler);
}