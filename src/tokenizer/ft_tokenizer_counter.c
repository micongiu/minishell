/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenizer_counter.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmedyns <anmedyns@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 16:40:02 by anmedyns          #+#    #+#             */
/*   Updated: 2024/12/30 16:40:06 by anmedyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_var_count	ft_count_dollar(char *input, t_env_var *env)
{
	t_var_count	count;

	count.i = 0;
	count.j = 0;
	if (ft_strlen(input, '$') == 0)
		input++;
	while (env)
	{
		if (ft_strncmp(input, env->name, ft_strlen_lib(env->name)) == 0)
		{
			count.i = ((int)ft_strlen_lib(env->value)) + 2;
			count.j = ((int)ft_strlen_lib(env->name));
			return (count);
		}
		env = env->next;
	}
	if (count.j == 0)
	{
		count.i += 2;
		count.j++;
	}
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
					count = ft_count_dollar(input + i, env);
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
			count = ft_count_dollar(input + i, env);
		if (input[i++] == '\0')
			return (i + count.i - count.j);
	}
	if (input[i] != ' ' && input[i] != '\0')
	{
		while (input[i] != ' ' && input[i] != '\0')
		{
			if (input[i] != '\"' && input[i] != '\0')
				if (input[i++] == '$')
					count = ft_count_dollar(input + i, env);
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
			count = ft_count_dollar(input + i, env);
			i += count.j;
		}
		else
			process_special_tokens(input, &i, &count.i);
	}
	i++;
	return (i - tmp + count.i - count.j);
}

int	ft_count_token(char *in)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (in[i] != '\0')
	{
		while (is_space(in[i]))
			i++;
		if (in[i] == '"' || in[i] == '\'')
		{
			while (in[i] != '"' && in[i] != '\'')
				i++;
			j++;
			i++;
		}
		j += handle_special_characters(in, &i);
		if (!is_space (in[i]))
		{
			j++;
			while (!is_space(in[i]) && ft_is_pipe_or_red(in[i]))
				i++;
		}
	}
	return (j);
}
