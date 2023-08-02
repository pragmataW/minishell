#include "../minishell.h"

int	ft_echo(char **args)
{
	int		i;
	int		n_flag;

	i = 1;
	n_flag = 0;
	if (args[1] && !ft_strncmp(args[1], "-n"))
	{
		n_flag = 1;
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (!n_flag)
		ft_putchar_fd('\n', 1);
	return (0);
}

int	ft_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	ft_putendl_fd(pwd, 1);
	free(pwd);
	return (0);
}

int	ft_env(void)
{
	int		i;
	t_env	*iter;

	i = 0;
	iter = data.env;
	while (iter->keys[i])
	{
		if (iter->values[i])
		{
			ft_putstr_fd(iter->keys[i], 1);
			ft_putchar_fd('=', 1);
			ft_putendl_fd(iter->values[i], 1);
		}
		i++;
	}
	return (0);
}

