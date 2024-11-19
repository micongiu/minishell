#include "../minishell.h"

t_var_count token_double_quote(char *token, char *line,
			t_env_var *env, t_var_count count)
{
	int	in_quotes;

	in_quotes = 1;
	count.i++;
	while (line[count.i] != '\0')
	{
		if (line[count.i] == '"')
			in_quotes = 0;
		else if (in_quotes == 0 && line[count.i] == ' ')
			break ;
		else if (line[count.i] == '$')
		{
			count = ft_ex_dollar(line, token, env, count);
			count.i++;
		}
		else
			token[count.j++] = line[count.i];
		count.i++;
	}
	token[count.j] = '\0';
	return count;
}

t_var_count	token_single_quote(char *token, char *line,
								t_env_var *env, t_var_count count)
{
	int	in_quotes;

	in_quotes = 1;
	count.i++;
	while (line[count.i] != '\0')
	{
		if (line[count.i] == '\'')
			in_quotes = 0;
		else if (in_quotes == 0 && line[count.i] == ' ')
			break ;
		else if (line[count.i] == '$' && in_quotes == 0)
		{
			count = ft_ex_dollar(line, token, env, count);
			count.i++;
		}
		else
			token[count.j++] = line[count.i];
		count.i++;
	}
	token[count.j] = '\0';
	return count;
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
		else if (line[count.i] == '$')
		{
			count = ft_ex_dollar(line, token, env, count);
			count.i++;
		}
		else
			token[count.j++] = line[count.i++];
	}
	return (count);
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
	tokens = ft_calloc(ft_count_token(input) + 1, sizeof (char *));
	while (input[count.i] != '\0')
	{
		while (is_space(input[count.i]))
			count.i++;
		if (input[count.i] == '\0')
			break;
		tmp = count.i;
		tokens[token_count] = ft_calloc(ft_count(input, tmp, env), sizeof (char));
		count.j = 0;
		count = token_separation(tokens[token_count++], input, env, count);
	}
	tokens[token_count] = NULL;
	return (tokens);
}
