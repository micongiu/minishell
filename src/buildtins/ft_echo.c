/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmedyns <anmedyns@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 16:04:58 by anmedyns          #+#    #+#             */
/*   Updated: 2025/01/02 19:55:30 by anmedyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

extern int	g_status;

int	ft_echo_utility(char *option)
{
	int	j;

	if (option && option[0] == '-' && option[1])
	{
		j = 1;
		while (option[j] == 'n')
			j++;
		if (option[j] == '\0')
			return (0);
	}
	return (1);
}

void	append_status(char *result, char *status_str, t_var_count *count)
{
	count->k = 0;
	while (status_str[count->k])
		result[(count->j)++] = status_str[(count->k)++];
}

void	process_status_loop(char *str, char *result, char *status_str,
		t_var_count *count)
{
	while (str[count->i] != '\0')
	{
		if (!count->quote_type && (str[count->i] == '\''
				|| str[count->i] == '\"'))
			count->quote_type = str[(count->i)++];
		else if (count->quote_type && str[count->i] == count->quote_type)
		{
			count->quote_type = 0;
			count->i++;
		}
		else if (count->quote_type != '\'' && str[count->i] == '$'
			&& str[count->i + 1] == '?')
		{
			append_status(result, status_str, count);
			count->i += 2;
		}
		else
			result[(count->j)++] = str[(count->i)++];
	}
	result[count->j] = '\0';
}

char	*process_status(char *str)
{
	char		*result;
	char		*status_str;
	t_var_count	count;

	if (!str)
		return (NULL);
	status_str = ft_itoa(g_status);
	if (!status_str)
		return (NULL);
	result = ft_calloc(ft_strlen_lib(str) + ft_strlen_lib(status_str) + 1,
			sizeof(char));
	if (!result)
		return (free(status_str), NULL);
	count.i = 0;
	count.j = 0;
	count.k = 0;
	count.quote_type = 0;
	process_status_loop(str, result, status_str, &count);
	free(status_str);
	return (result);
}

void	ft_echo(t_process_list *info_process)
{
	int		i;
	int		newline;
	char	*tmp;

	i = 1;
	tmp = NULL;
	newline = ft_echo_utility(info_process->option);
	if (newline == 0)
		i++;
	while (info_process->argument[i])
	{
		if (ft_strlen_lib(info_process->argument[i]) > 0)
		{
			tmp = process_status(info_process->argument[i]);
			if (ft_strlen_lib(tmp) > 0)
				ft_putstr_fd(tmp, STDOUT_FILENO);
			free(tmp);
		}
		if (info_process->argument[i + 1] && info_process->argument[i + 1][0])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (newline == 1)
		write(STDOUT_FILENO, "\n", 1);
	g_status = 0;
}
