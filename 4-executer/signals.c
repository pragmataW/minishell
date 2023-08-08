#include "../minishell.h"

static void	handle_sigint(int sig)
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
	{
		g_data.heredoc = 0;
		exit(0);
	}
}

void	signals_control(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}
