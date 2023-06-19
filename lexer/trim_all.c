#include "../minishell.h"

static void	trim_all_extra(t_list **ret, t_list *iter, int i, int j)
{
	char	*will_push;

	while (iter->command[i])
	{
		will_push = malloc(sizeof(char) * command_len(&(iter->command[i])) + 1);
		if (iter->command[i] == '|' || iter->command[i] == '<'
			|| iter->command[i] == '>')
		{
			if (iter->command[i] == '<' && iter->command[i + 1] == '<')
			{
				ft_lstadd_back(ret, ft_lstnew("<<"));
				i = i + 2;
			}
			else if (iter->command[i] == '>' && iter->command[i + 1] == '>')
			{
				ft_lstadd_back(ret, ft_lstnew(">>"));
				i = i + 2;
			}
			else
			{
				will_push[0] = iter->command[i];
				will_push[1] = '\0';
				ft_lstadd_back(ret, ft_lstnew(will_push));
				i++;
			}
		}
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
		if (!ft_strchr(iter->command, '|') && !ft_strchr(iter->command, '<')
			&& !ft_strchr(iter->command, '>'))
			ft_lstadd_back(ret, ft_lstnew(iter->command));
		else
			trim_all_extra(ret, iter, 0, 0);
		iter = iter->next;
	}
	return (ret);
}

// int main ()
// {
// 	t_list **splitted_str;
// 	t_list **ret;

// 	//splitted_str = malloc(sizeof(t_list *));
// 	*splitted_str = NULL;
// 	ft_lstadd_back(splitted_str, ft_lstnew("catls"));
// 	ret = trim_all(splitted_str);
// 	printf("%s\n", (*ret)->command);
// 	printf("%s\n", (*ret)->next->command);
// 	printf("%s\n", (*ret)->next->next->command);
// 	//system("leaks a.out");
// 	return (0);
// }
