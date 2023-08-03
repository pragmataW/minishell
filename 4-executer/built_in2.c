#include "../minishell.h"

static void	go_home(void)
{
	char	*path;

	path = find_values(data.env, "HOME", NULL);
	set_value("OLDPWD", getcwd(NULL, 0));
	chdir(path);
	set_value("PWD", getcwd(NULL, 0));
}

static void	go_oldpwd(void)
{
	char	*path;

	path = find_values(data.env, "OLDPWD", NULL);
	set_value("OLDPWD", getcwd(NULL, 0));
	chdir(path);
	set_value("PWD", getcwd(NULL, 0));
}

static void	go_path(char **args)
{
	char	*path;

	path = args[1];
	set_value("OLDPWD", getcwd(NULL, 0));
	chdir(path);
	set_value("PWD", getcwd(NULL, 0));
}

int	ft_cd(char **args)
{

	if (args[1] == NULL)
		go_home();
	else if (args[1][0] == '-' && args[1][1] == '\0')
		go_oldpwd();
	else
		go_path(args);
	return (0);
}
