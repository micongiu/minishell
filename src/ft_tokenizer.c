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
int	ft_fake_tokenizer(char *input)
{
	int i;
	int j;
	int in_token;

	j = 0;
	i = 0;
	in_token = 0;

	while (input[i] != '\0')
	{
		if (input[i] == '"')
		{
			i++;
			while(input[i] != '"' && input[i] != '\0')
				i++;
		}
		if (input[i] == '\'')
		{
			i++;
			while(input[i] != '\'' && input[i] != '\0')
				i++;
		}
		if (!isspace(input[i]) && !in_token)
		{
			in_token = 1;
			j++;
		}
		else if (isspace(input[i]) && in_token)
			in_token = 0;
		i++;
	}
	j++;
	return (j);
}

char	**ft_tokenizer(char *input, t_env_var *env)
{
	char		**tokens;
	int			token_count;
	t_var_count count;

	count.i = 0;
	count.j = 0;
	token_count = 0;
	tokens = ft_calloc(ft_fake_tokenizer(input), sizeof (char *));
	printf(" numero fake_token = %i", ft_fake_tokenizer(input));
	while (input[count.i] != '\0')
	{
		while (is_space(input[count.i]))
			count.i++;
		if (input[count.i] == '\0')
			break;
		tokens[token_count] = ft_calloc(MAX_TOKEN_LEN, sizeof (char));
		count.j = 0;
		count = token_separation(tokens[token_count], input, env, count);
		tokens[token_count][count.j] = '\0';
		token_count++;
	}
	tokens[token_count] = NULL;
	printf(" PORCMAONNA\n");
	return (tokens);
}
