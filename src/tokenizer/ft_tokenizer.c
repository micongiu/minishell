/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmedyns <anmedyns@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 16:14:16 by anmedyns          #+#    #+#             */
/*   Updated: 2024/12/30 16:44:02 by anmedyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_var_count	token_double_quote(char *token, char *line,
			t_env_var *env, t_var_count count)
{
	int	in_quotes;

	in_quotes = 1;
	token[count.j++] = line[count.i];
	count.i++;
	while (line[count.i] != '\0')
	{
		if (line[count.i] == '"')
		{
			in_quotes = 0;
			count.i++;
		}
		else if (in_quotes == 0 && line[count.i] == ' ')
			break ;
		else if (is_special_token_after_quotes(line, count.i)
			&& !is_space(line[count.i]) && in_quotes == 0)
			break ;
		else if (line[count.i] == '$' && line[count.i + 1])
			count = ft_ex_dollar(line, token, env, count);
		else
			token[count.j++] = line[count.i++];
	}
	token[count.j] = '"';
	return (count);
}

t_var_count	token_single_quote(char *token, char *line,
								t_env_var *env, t_var_count count)
{
	int	in_quotes;

	in_quotes = 1;
	token[count.j++] = line[count.i];
	count.i++;
	while (line[count.i] != '\0')
	{
		if (line[count.i] == '\'')
			in_quotes = 0;
		else if (in_quotes == 0 && line[count.i] == ' ')
			break ;
		else if (is_special_token_after_quotes(line, count.i)
			&& !is_space(line[count.i]) && in_quotes == 0)
			break ;
		else if (line[count.i] == '$' && line[count.i + 1])
			count = ft_ex_dollar(line, token, env, count);
		else
			token[count.j++] = line[count.i];
		count.i++;
	}
	token[count.j] = '\'';
	return (count);
}

t_var_count	token_separation(char *token, char *line,
								t_env_var *env, t_var_count co)
{
	while (line[co.i] != '\0' && !is_space(line[co.i]))
	{
		if (line[co.i] == '"')
		{
			co = token_double_quote(token, line, env, co);
			break ;
		}
		else if (line[co.i] == '\'')
		{
			co = token_single_quote(token, line, env, co);
			break ;
		}
		else if (line[co.i] == '$' && line[co.i + 1])
			co = ft_ex_dollar((line + co.i), token, env, co);
		else if (line[co.i] == '|' || line[co.i] == '<' || line[co.i] == '>')
		{
			if (co.j > 0)
				break ;
			co = handlett_special_tokens(token, line, co);
			break ;
		}
		else
			token[co.j++] = line[co.i++];
	}
	return (token[co.j] = '\0', co);
}

char	**ft_tokenizer(char *input, t_env_var *env)
{
	char		**tokens;
	int			t_count;
	t_var_count	count;

	count.i = 0;
	count.j = 0;
	count.k = 0;
	t_count = 0;
	if (ft_check_quote(input) == -1)
		return (ft_putendl_fd("minishell->Error: Unclosed quotes", 1), NULL);
	tokens = ft_calloc(ft_count_token(input) + 2, sizeof (char **));
	count.k = ft_count_token(input) + 1;
	while (t_count < count.k)
	{
		while (is_space(input[count.i]))
			count.i++;
		tokens[t_count] = (char *)ft_calloc(ft_count(input, count.i, env),
				sizeof(char));
		count.j = 0;
		count = token_separation(tokens[t_count++], input, env, count);
	}
	free(input);
	return (tokens);
}

int	handle_special_characters(char *input, int *i)
{
	int	count;

	count = 0;
	if (input[*i] == '<' && input[*i + 1] == '<')
	{
		count++;
		*i += 2;
	}
	else if (input[*i] == '>' && input[*i + 1] == '>')
	{
		count++;
		*i += 2;
	}
	else if (input[*i] == '|' || input[*i] == '<' || input[*i] == '>')
	{
		count++;
		(*i)++;
	}
	return (count);
}
