#include "../minishell.h"

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

int	ft_count_len(char *input, int i)
{
	i++;
	while (input[i] != '\"' && input[i] != '\''  && input[i] != '\0')
		i++;
	if (input[i] == '\0')
	{
		i++;
		return (i);
	}
	if (input[i] != ' ' && input[i] != '\0')
	{
		while (input[i] != ' ' && input[i] != '\0')
		{
			if (input[i] != '\"' && input[i] != '\'' && input[i] != '\0')
				i++;
			if (input[i] == '\0' || input[i] == ' ')
				break ;
			i++;
		}
	}
	return (i);
}

int	ft_count(char *input, int i)
{
	int	tmp;

	tmp = i;
	while (input[i] != '\0' && !is_space(input[i]))
	{
		if (input[i] == '"' || input[i] == '\'')
		{
			i = ft_count_len(input, i);
			return (i - tmp - 1);
		}
		i++;
	}
	i++;
	return (i - tmp);
}

int	ft_count_token(char *input)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while(input[i] != '\0')
	{
		while(is_space(input[i]))
			i++;
		if(input[i++] == '"' || input[i++] == '\'')
		{
			while(input[i] != '"' && input[i] != '\'')
				i++;
			j++;
			i++;
		}
		if(!is_space(input[i]))
		{
			j++;
			while(!is_space(input[i]) && input[i] != '\0')
				i++;
		}
	}
	return (j);
}
