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
char	**lexer(char *prompt, int i, int j, int end);
int		word_count(char *prompt, int counter, int i, char quotes);

#endif