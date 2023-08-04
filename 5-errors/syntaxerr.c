#include "../minishell.h"

void	parse_error(t_table *iter)
{
	terminate_command(iter);
	printf("minishell: parse error no file\n");
}

void	too_argumenst(t_table *iter)
{
	terminate_command(iter);
	printf("minishell: parse error too many arguments\n");
}

void	command_not_found(void)
{
	if (data.status == 127)
		printf("minishell: command cannot execute (not found or syntax err)\n");
	data.status = 0;
}
