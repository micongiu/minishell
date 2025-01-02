/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utility_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: micongiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 16:33:23 by micongiu          #+#    #+#             */
/*   Updated: 2024/12/27 16:33:25 by micongiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_status;

int	ft_is_pipe_or_red(char c)
{
	if (c != '\0' && !(c == '|' || c == '<' || c == '>'))
		return (1);
	return (0);
}

char	get_first_quote(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '\"')
			return (str[i]);
		i++;
	}
	return (0);
}

char	*remove_quotes(char *str)
{
	int		i;
	int		j;
	char	*new_str;
	char	quote_type;

	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	quote_type = get_first_quote(str);
	new_str = ft_calloc((ft_strlen_lib(str) + 1), sizeof(char));
	if (!new_str)
		return (NULL);
	while (str[i] != '\0')
	{
		if (str[i] != quote_type)
			new_str[j++] = str[i];
		i++;
	}
	new_str[j] = '\0';
	return (new_str);
}

t_var_count	handle_dollar_question(char **line, char **token, t_var_count count)
{
	(*token)[count.j++] = **line;
	(*line)++;
	(*token)[count.j++] = **line;
	(*line)++;
	count.i += 2;
	return (count);
}

t_var_count	ft_ex_dollar(char *line, char *token,
	t_env_var *env, t_var_count count)
{
	int	j;
	int	tmp;

	while (line && *line != '$')
		line++;
	if (*line == '$' && (*(line + 1) == '?'))
		return (count = handle_dollar_question(&line, &token, count));
	line++;
	while (env)
	{
		j = 0;
		tmp = count.j;
		if (ft_strncmp(line, env->name, ft_strlen_lib(env->name)) == 0)
		{
			while (env->value[j])
				token[tmp++] = env->value[j++];
			count.i += ft_strlen(line, ' ') + 1;
			count.j += tmp;
			break ;
		}
		env = env->next;
	}
	if (env == NULL)
		count.i++;
	return (count);
}
