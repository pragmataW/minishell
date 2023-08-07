#include "../minishell.h"

int	ft_echo(char **args)
{
	int	i;
	int	n_flag;

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
	int	i;

	i = 0;
	while (g_data.env->keys[i])
	{
		if (g_data.env->values[i])
		{
			ft_putstr_fd(g_data.env->keys[i], 1);
			ft_putchar_fd('=', 1);
			ft_putendl_fd(g_data.env->values[i], 1);
		}
		i++;
	}
	return (0);
}

int	ft_unset(char **args, int i)
{
	char	*tmp;
	int		index;

	while (args[i])
	{
		tmp = find_values(g_data.env, args[i], &index);
		if (tmp)
			free(tmp);
		else
		{
			i++;
			continue ;
		}
		free(g_data.env->keys[index]);
		g_data.env->keys[index] = ft_strdup(" ");
		free(g_data.env->values[index]);
		g_data.env->values[index] = ft_strdup(" ");
		g_data.env->keys = resize_matrix(g_data.env->keys);
		g_data.env->values = resize_matrix(g_data.env->values);
		i++;
	}
	return (0);
}

int	ft_export(char **args)
{
	int		i;
	char	**key_value;

	i = 1;
	while (args[i])
	{
		if (!is_exportable(args[i]))
		{
			i++;
			continue ;
		}
		key_value = ft_split(args[i], '=');
		export_keywords(key_value[0], 0);
		export_value(key_value[1]);
		free_matrix(key_value);
		i++;
	}
	return (0);
}
