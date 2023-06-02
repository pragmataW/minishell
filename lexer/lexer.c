#include "../minishell.h"

static int	word_count(char *prompt, int counter, int i, char quotes)
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

char	**lexer(char *prompt, int i, int j, int end)
{
	char	**ret;
	char	*tmp;

	ret = malloc(sizeof(char *) * word_count(prompt, 0, 0, 0) + 1);
	ret[word_count(prompt, 0, 0, 0)] = NULL;
	while (prompt[end])
		end++;
	while (prompt[end] == ' ' || prompt[end] == '\t' || prompt[end] == '\0')
		end--;
	while (prompt[i] && i <= end)
	{
		while ((prompt[i] == ' ' || prompt[i] == '\t') && prompt[i] != '\0')
			i++;
		tmp = &prompt[i];
		while (prompt[i] != ' ' && prompt[i] != '\t' && prompt[i] != '\0')
		{
			if (prompt[i] == 34 || prompt[i] == 39)
				quotes_skipper(&i, prompt);
			i++;
		}
		ret[j] = malloc(sizeof(char) * ((&(prompt[i]) - tmp) + 1));
		allocator(ret[j], tmp, &(prompt[i]) - tmp);
		j++;
	}
	return (ret);
}
