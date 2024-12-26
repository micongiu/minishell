#include "../../minishell.h"

t_var_count	ft_count_dollar(char *input, t_env_var *env)
{
	t_var_count	count;

	count.i = 0;
	count.j = 0;
	while (input && *input != '$')
		input++;
	input++;
	while (env)
	{
		if (ft_strncmp(input, env->name, ft_strlen_lib(env->name)) == 0)
		{
			count.i = ((int)ft_strlen_lib(env->value));
			count.j = ((int)ft_strlen_lib(env->name)) + 1;
			return (count);
		}
		env = env->next;
	}
	if (count.j == 0)
		count.j++;
	return (count);
}

int	ft_count_len_sqoute(char *input, int i, t_env_var *env)
{
	t_var_count	count;

	count.i = 0;
	count.j = 0;
	i++;
	while (input[i] != '\'' && input[i] != '\0')
		i++;
	if (input[i] == '\0')
		return (++i);
	if (input[i] != ' ' && input[i] != '\0')
	{
		while (input[i] != ' ' && input[i] != '\0')
		{
			if (input[i] != '\'' && input[i] != '\0')
			{
				if (input[i] == '$')
					count = ft_count_dollar(input, env);
				i++;
			}
			if (input[i] == '\0' || input[i] == ' ')
				break ;
			i++;
		}
	}
	return (i + count.i - count.j + 2);
}

int	ft_count_len_dqoute(char *input, int i, t_env_var *env)
{
	t_var_count	count;

	count.i = 0;
	count.j = 0;
	i++;
	while (input[i] != '\"' && input[i] != '\0')
	{
		if (input[i] == '$')
			count = ft_count_dollar(input, env);
		if (input[i++] == '\0')
			return (i + count.i - count.j);
	}
	if (input[i] != ' ' && input[i] != '\0')
	{
		while (input[i] != ' ' && input[i] != '\0')
		{
			if (input[i] != '\"' && input[i] != '\0')
				if (input[i++] == '$')
					count = ft_count_dollar(input, env);
			if (input[i] == '\0' || input[i] == ' ')
				break ;
			i++;
		}
	}
	return (i + count.i - count.j + 2);
}

int	ft_count(char *input, int i, t_env_var *env)
{
	int			tmp;
	t_var_count	count;

	count.i = 0;
	count.j = 0;
	tmp = i;
	while (input[i] != '\0' && !is_space (input[i]))
	{
		if (input[i] == '"')
			return ((ft_count_len_dqoute(input, i, env)) - tmp - 1);
		else if (input[i] == '\'')
			return ((ft_count_len_sqoute(input, i, env)) - tmp - 1);
		else if (input[i] == '$' && input[i + 1])
		{
			count = ft_count_dollar(input, env);
			i += count.j;
		}
		else
			process_special_tokens(input, &i, &count.i);
	}
	i++;
	return (i - tmp + count.i - count.j);
}

int	ft_count_token(char *input)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (input[i] != '\0')
	{
		while (is_space (input[i]))
			i++;
		if (input[i] == '"' || input[i] == '\'')
		{
			while (input[i] != '"' && input[i] != '\'')
				i++;
			j++;
			i++;
		}
		j += handle_special_characters(input, &i);
		if (!is_space (input[i]))
		{
			j++;
			while (!is_space(input[i]) && input[i] != '\0' && !(input[i] == '|' || input[i] == '<' || input[i] == '>'))
				i++;
		}
	}
	return (j);
}
