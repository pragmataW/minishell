#include "../minishell.h"

void	pipe_syntax_check(t_list **lexed_str)
{
	t_list	*i;

	i = *lexed_str;
	if (!i)
		return ;
	if (i->command[0] == '|')
	{
		data.err = 1;
		return ;
	}
	while (i)
	{
		if (i->command[0] == '|' && (i->next == NULL
				|| i->next->command[0] == '>'
				|| i->next->command[0] == '<' || i->next->command[0] == '|'))
		{
			data.err = 1;
			return ;
		}
		i = i->next;
	}
}

void	redirec_syntax_check(t_list **lexed_str)
{
	t_list	*i;

	i = *lexed_str;
	if (!i)
		return ;
	if (i->command[0] == '>' || i->command[0] == '<')
	{
		data.err = 1;
		return ;
	}
	while (i)
	{
		if ((i->command[0] == '<' || i->command[0] == '>') && (i->next == NULL
				|| i->next->command[0] == '>'
				|| i->next->command[0] == '<' || i->next->command[0] == '|'))
		{
			data.err = 1;
			return ;
		}
		i = i->next;
	}
}
