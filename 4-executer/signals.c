#include "../minishell.h"

void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

void	heredoc_sig(int sig)
{
	if (sig == SIGINT)
		exit(0);
}

void	segfault_handler(int sig)
{
	if (sig == SIGSEGV)
		exit(0);
}

void	signals_control(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGSEGV, segfault_handler);
	signal(SIGQUIT, SIG_IGN);
}
