#include "../minishell.h"

static void	special_char_trim(int * i, t_list *iter, t_list **ret, char *w_p)
{
	if (iter->command[*i] == '<' && iter->command[*i + 1] == '<')
	{
		ft_lstadd_back(ret, ft_lstnew("<<"));
		*i = *i + 2;
	}
	else if (iter->command[*i] == '>' && iter->command[*i + 1] == '>')
	{
		ft_lstadd_back(ret, ft_lstnew(">>"));
		*i = *i + 2;
	}
	else
	{
		w_p[0] = iter->command[*i];
		w_p[1] = '\0';
		ft_lstadd_back(ret, ft_lstnew(w_p));
		*i += 1;
	}
}

static void	trim_all_extra(t_list **ret, t_list *iter, int i, int j)
{
	char	*will_push;

	while (iter->command[i])
	{
		will_push = malloc(sizeof(char) * command_len(&(iter->command[i])) + 1);
		if (iter->command[i] == '|' || iter->command[i] == '<'
			|| iter->command[i] == '>')
			special_char_trim(&i, iter, ret, will_push);
		else
		{
			j = 0;
			while (iter->command[i] != '|' && iter->command[i] != '<'
				&& iter->command[i] != '>' && iter->command[i] != '\0')
			{
				will_push[j] = iter->command[i];
				i++;
				j++;
			}
			will_push[j] = '\0';
			ft_lstadd_back(ret, ft_lstnew(will_push));
		}
	}
}

t_list	**trim_all(t_list **splited_str)
{
	t_list	**ret;
	t_list	*iter;
	char	*tmp;

	ret = malloc(sizeof(t_list *));
	*ret = NULL;
	iter = *splited_str;
	while (iter)
	{
		if ((!ft_strchr(iter->command, '|') && !ft_strchr(iter->command, '<')
				&& !ft_strchr(iter->command, '>')) || iter->command[0] == '\"'
			|| iter->command[0] == 39)
			ft_lstadd_back(ret, ft_lstnew(iter->command));
		else
			trim_all_extra(ret, iter, 0, 0);
		iter = iter->next;
	}
	return (ret);
}
