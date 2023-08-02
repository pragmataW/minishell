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
# include <sys/wait.h>
# include "libft/libft.h"

typedef struct s_env
{
	char	**keys;
	char	**values;
	char	*tilda;
}			t_env;

typedef struct s_table
{
	char			*cmd_path;
	char			**full_cmd;
	int				infile;
	int				outfile;
	struct s_table	*next;
}				t_table;

typedef struct s_data
{
	t_env			*env;
	struct s_table	**cmd_table;
	int				process_count;
	int				counter;
}				t_data;


extern t_data	data;

//! MAIN
void		free_list(t_list **list, char *prompt);
//! LEXER
t_list		**lexer(char *prompt, int i, int j, int end);
t_list		**trim_all(t_list **splited_str);
//! LEXER UTILS
void		allocator(char *ret, char *src, int len);
void		quotes_skipper(int *i, char *prompt);
int			command_len(char *cmd);
//! INIT_ENV
t_env		*env_variables(char **env, int env_count);
//! INIT_ENV UTILS
int			find_char(char *str, char c);
//!EXPANDER UTILS
void		expand_quote(t_list *iter, int *i, char *new_str, int *j);
void		expand_single_quote(t_list *iter, int *i, char *new_str, int *j);
void		expand_dollar(t_list *iter, int *i, char *new_str, int *j);
void		tilda_extra(t_list *iter, int *i, char *new_str, int *k);
//! EXPANDER UTILS EXTRA
char		*find_values(t_env *env, char *kw);
char		*ft_str_realloc(char *str);
void		expand_normal(t_list *iter, int *i, char *new_str, int *j);
void		new_command(t_list *iter, char *str);
//! EXPANDER
void		expander(t_list **splitted_str, char **env);
//! PARSER UTILS
void		table_add_back(t_table **lst, t_table *new);
t_table		*table_last(t_table *lst);
t_table		*table_new(void);
char		*find_path(char *path, char *command);
//! EXPAND_CMD
int			is_builtin(char *cmd);
void		expand_cmd(t_table **table, t_env *env, int i);
void		expand_binary(t_table *node);
//! FILLNODE
int			node_counter(t_list *list);
t_table		**fill_node(t_list **list, int i);
//! PARSER
t_table		**parser(t_list **expanded_str);
//!EXECUTER
void		executer(t_table **cmd_table, int i, int j);
//! EXECUTER UTILS
int			process_counter(t_table **cmd_table);
int			**create_pipes(int process_count);
//! FD_DUPS
void		single_exec(t_table *iter);
void		dup_first(t_table *iter, int **fd);
void		dup_last(t_table *iter, int **fd, int pc);
void		dup_mids(t_table *iter, int **fd, int j);
void		close_main_fd(int **fd, int j, int i, int pc);
#endif