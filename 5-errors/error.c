#include "../minishell.h"

void	errors(t_list **lexed_str, char *prompt)
{
	char	*last_status;

	quote_check(lexed_str, 0);
	pipe_syntax_check(lexed_str);
	redirec_syntax_check(lexed_str);
	if (data.err == 1)
	{
		printf("minishell: syntax error\n");
		data.status = 2;
		last_status = ft_itoa(data.status);
		set_value("?", last_status);
		add_history(prompt);
	}
}
