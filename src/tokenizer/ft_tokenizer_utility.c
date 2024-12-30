/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenizer_utility.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmedyns <anmedyns@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 16:47:26 by anmedyns          #+#    #+#             */
/*   Updated: 2024/12/30 16:47:32 by anmedyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	process_special_tokens(char *input, int *i, int *count_i)
{
	int	special_token_count;

	special_token_count = handle_special_characters(input, i);
	if (special_token_count > 0)
	{
		*count_i += special_token_count;
		return (1);
	}
	else
	{
		(*i)++;
		return (0);
	}
}

t_var_count	handlett_special_tokens(char *token, char *line, t_var_count count)
{
	if ((line[count.i] == '<' && line[count.i + 1] == '<')
		|| (line[count.i] == '>' && line[count.i + 1] == '>'))
	{
		token[count.j++] = line[count.i++];
		token[count.j++] = line[count.i++];
	}
	else if (line[count.i] == '|' || line[count.i]
		== '<' || line[count.i] == '>')
	{
		token[count.j++] = line[count.i++];
	}
	token[count.j] = '\0';
	return (count);
}

int	is_special_token_after_quotes(char *line, int i)
{
	if (line[i] == '|' || line[i] == '<' || line[i] == '>')
	{
		if (line[i + 1] == line[i])
		{
			return (1);
		}
		return (1);
	}
	return (0);
}
