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

//! LEXER
t_list	**lexer(char *prompt, int i, int j, int end);
t_list	**trim_all(t_list **splited_str);
//! LEXER UTILS
char	*allocator(char *ret, char *src, int len);
void	quotes_skipper(int *i, char *prompt);
int		command_len(char *cmd);
#endif