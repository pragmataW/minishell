#include "../minishell.h"

char	*allocator(char *ret, char *src, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		ret[i] = src[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

void	quotes_skipper(int *i, char *prompt)
{
	char	quotes;

	quotes = prompt[*i];
	*i = *i + 1;
	while (prompt[*i] != quotes)
		*i = *i + 1;
}