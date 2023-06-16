#include "../minishell.h"

static void	lexer_extra(char *prompt, int *i, char **tmp)
{
	while ((prompt[*i] == ' ' || prompt[*i] == '\t') && prompt[*i] != '\0')
			*i = *i + 1;
	*tmp = &prompt[*i];
	while (prompt[*i] != ' ' && prompt[*i] != '\t' && prompt[*i] != '\0')
	{
		if (prompt[*i] == 34 || prompt[*i] == 39)
			quotes_skipper(i, prompt);
		*i = *i + 1;
	}
}

t_list	**lexer(char *prompt, int i, int j, int end)
{
	t_list	*cmd;
	t_list	**root;
	char	*command;
	char	*tmp;

	root = malloc(sizeof(t_list *));
	*root = NULL;
	while (prompt[end])
		end++;
	while (prompt[end] == ' ' || prompt[end] == '\t' || prompt[end] == '\0')
		end--;
	while (prompt[i] && i <= end)
	{
		lexer_extra(prompt, &i, &tmp);
		command = malloc(sizeof(char) * ((&(prompt[i]) - tmp) + 1));
		allocator(command, tmp, &(prompt[i]) - tmp);
		cmd = ft_lstnew(command);
		ft_lstadd_back(root, cmd);
		j++;
	}
	return (root);
}
