#include "../minishell.h"

int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f');
}

t_var_count	token_double_quote(char *token, char *line,
								t_env_var *env, t_var_count count)
{
	count.i++;
	while(is_space(line[count.i]))
		count.i++;
	while (line[count.i] != '"' && line[count.i] != '\0')
		token[count.j++] = line[count.i++];
	count.i++;
	if (line[count.i] != ' ' && line[count.i] != '\0')
	{
		while (line[count.i] != ' ' && line[count.i] != '\0')
		{
			if (line[count.i] == '"' && line[count.i] != '\0')
				count.i++;
			if (line[count.i] == '\0')
				break ;
			token[count.j++] = line[count.i++];
		}
	}
	if (line[count.i] != '\0')
		token[count.j++] = '\0';
	return (count);
}

t_var_count	token_single_quote(char *token, char *line,
								t_env_var *env, t_var_count count)
{
	count.i++;
	while (line[count.i] != '\'' && line[count.i] != '\0')
		token[count.j++] = line[count.i++];
	count.i++;
	if (line[count.i] != ' ' && line[count.i] != '\0')
	{
		while (line[count.i] != ' ' && line[count.i] != '\0')
		{
			if (line[count.i] == '\'' && line[count.i] != '\0')
				count.i++;
			if (line[count.i] == '\0')
				break ;
			token[count.j++] = line[count.i++];
		}
	}
	if (line[count.i] != '\0')
		token[count.j++] = '\0';
	return (count);
}

t_var_count	token_separation(char *token, char *line,
								t_env_var *env, t_var_count count)
{
	while (line[count.i] != '\0' && !is_space (line[count.i]))
	{
		if (line[count.i] == '"')
		{
			count = token_double_quote(token, line, env, count);
			break ;
		}
		else if (line[count.i] == '\'')
		{
			count = token_single_quote(token, line, env, count);
			break ;
		}
		token[count.j++] = line[count.i++];
	}
	return (count);
}

int	ft_count_len(char *input, int i)
{
	while (input[i] != '\"' && input[i] != '\''  && input[i] != '\0')
		i++;
	if (input[i] == '\0')
	{
		i++;
		return (i);
	}
	i++;
	if (input[i] != ' ' && input[i] != '\0')
	{
		while (input[i] != ' ' && input[i] != '\0')
		{
			if (input[i] != '\"' && input[i] != '\'' && input[i] != '\0')
				i++;
			if (input[i] == '\0')
				break ;
			i++;
		}
	}
	return (i);
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

int	ft_count(char *input, int i)
{
	while (input[i] != '\0' && !is_space (input[i]))
	{
		if (input[i] == '"' && input[i] == '\'')
		{
			i = ft_count_len(input, i);
			return (i);
		}
		i++;
	}
	i++;
	return (i);
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
		if(input[i] == '"')
		{
			i++;
			while(input[i] != '"')
				i++;
			j++;
			i++;
		}
		if(input[i] == '\'')
		{
			i++;
			while(input[i] != '\'')
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

char	**ft_tokenizer(char *input, t_env_var *env)
{
	char		**tokens;
	int			token_count;
	int			tmp;
	t_var_count count;

	count.i = 0;
	count.j = 0;
	tmp = 0;
	token_count = 0;
	if (ft_check_quote(input) == -1)
		return (ft_putendl_fd("minishell->Error: Unclosed quotes", 1), NULL);
	tokens = ft_calloc(ft_count_token(input), sizeof (char *));
	// printf("%d\n", ft_count_token(input));
	while (input[count.i] != '\0')
	{
		while (is_space(input[count.i]))
			count.i++;
		if (input[count.i] == '\0')
			break;
		tmp = count.i;
		tokens[token_count] = ft_calloc(ft_count_len(input, tmp), sizeof (char));
		count.j = 0;
		count = token_separation(tokens[token_count], input, env, count);
		tokens[token_count][count.j] = '\0';
		token_count++;
	}
	tokens[token_count] = NULL;
	return (tokens);
}
