#include "../minishell.h"

void	errors(t_list **lexed_str, char *prompt)
{
	char	*last_status;

	pipe_syntax_check(lexed_str);
	redirec_syntax_check(lexed_str);
	if (g_data.err == 1)
	{
		printf("minishell: syntax error\n");
		g_data.status = 2;
		last_status = ft_itoa(g_data.status);
		set_value("?", last_status);
		free(last_status);
		add_history(prompt);
	}
}

