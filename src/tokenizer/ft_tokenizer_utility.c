#include "../../minishell.h"

int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f');
}

int	ft_check_quote(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '"')
		{
			i++;
			while (input[i] && input[i] != '"')
				i++;
			if (input[i] == '\0')
				return (-1);
		}
		if (input[i] == '\'')
		{
			i++;
			while (input[i] && input[i] != '\'')
				i++;
			if (input[i] == '\0')
				return (-1);
		}
		i++;
	}
	return (0);
}
