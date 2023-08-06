#include "../minishell.h"

void	parse_error(t_table *iter)
{
	terminate_command(iter);
	printf("minishell: parse error no file\n");
	data.status = 2;
}

void	too_argumenst(t_table *iter)
{
	terminate_command(iter);
	printf("minishell: parse error too many arguments\n");
	data.status = 2;
}

void	command_not_found(void)
{
	if (data.status == 127)
		printf("minishell: command cannot execute (not found or syntax err)\n");
	data.status = 0;
}

void	quote_check(t_list **lexed_str, int i)
{
	t_list	*iter;
	char	quote;

	iter = *lexed_str;
	while (iter)
	{
		i = 0;
		while (iter->command[i])
		{
			if (iter->command[i] == '\'' || iter->command[i] == '\"')
			{
				quote = iter->command[i];
				i++;
				while (iter->command[i] && iter->command[i] != quote)
					i++;
				if (iter->command[i] == '\0')
				{
					data.err = 1;
					return ;
				}
			}
			i++;
		}
		iter = iter->next;
	}
}
