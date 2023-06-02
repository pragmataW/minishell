#include "../minishell.h"

int	word_count(char *prompt, int counter, int i, char quotes)
{
	int	end;

	end = 0;
	while (prompt[end])
		end++;
	while (prompt[end] == ' ' || prompt[end] == '\t' || prompt[end] == '\0')
		end--;
	while (prompt[i] && i <= end)
	{
		while ((prompt[i] == ' ' || prompt[i] == '\t') && prompt[i] != '\0')
			i++;
		while (prompt[i] != ' ' && prompt[i] != '\t' && prompt[i] != '\0')
		{
			if (prompt[i] == 34 || prompt[i] == 39)
			{
				quotes = prompt[i];
				i++;
				while (prompt[i] != quotes)
					i++;
			}
			i++;
		}
		counter++;
	}
	return (counter);
}

char	**lexer(char *prompt, int i)
{
	char	**ret;

	ret = malloc(sizeof(char *) * word_count(prompt, 0, 0, 0));
	while (ret[i])
	{
		
	}
}
