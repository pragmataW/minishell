#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>
# include "libft/libft.h"

typedef struct s_env
{
	char	**keys;
	char	**values;
	char	*tilda;
}			t_env;

typedef struct s_data
{
	t_list	**trimmed_str;
	t_env	*env;
	int		mshell_pid;
	int		last_ret;
}				t_data;

//! MAIN
void	free_list(t_list **list);
//! LEXER
t_list	**lexer(char *prompt, int i, int j, int end);
t_list	**trim_all(t_list **splited_str);
//! LEXER UTILS
char	*allocator(char *ret, char *src, int len);
void	quotes_skipper(int *i, char *prompt);
int		command_len(char *cmd);
//! INIT_ENV
t_env	*env_variables(char **env, int env_count);
//! INIT_ENV UTILS
int		find_char(char *str, char c);
//!EXPANDER UTILS
char	*find_values(t_env *env, char *kw);
#endif