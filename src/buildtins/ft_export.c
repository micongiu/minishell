/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmedyns <anmedyns@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 16:05:22 by anmedyns          #+#    #+#             */
/*   Updated: 2025/01/03 15:53:58 by anmedyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_export_utility(t_env_var *tmp, char *str_name, char *str_value,
		t_env_var **env)
{
	char	*new_str_name;
	char	*new_str_value;

	new_str_name = NULL;
	new_str_value = NULL;
	while (tmp)
	{
		if (ft_strncmp(str_name, (tmp)->name, ft_strlen_lib((tmp)->name)) == 0)
		{
			free((tmp)->value);
			(tmp)->value = ft_strdup_lib(str_value);
			free(str_value);
			return (free(str_name));
		}
		tmp = (tmp)->next;
	}
	new_str_name = remove_quotes(str_name);
	new_str_value = remove_quotes(str_value);
	ft_add_env_var(env, new_str_name, new_str_value);
	free(str_name);
	free(str_value);
}

void	ft_export_null(t_env_var *env)
{
	t_env_var	*current;

	current = env;
	while (current != NULL)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(current->name, STDOUT_FILENO);
		ft_putchar_fd('=', STDOUT_FILENO);
		ft_putstr_fd(current->value, STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		current = current->next;
	}
}

int	ft_find_equal(t_process_list **process)
{
	int	i;

	i = 0;
	while ((*process)->argument[1][i] && (*process)->argument[1][i] != '=')
		i++;
	if (i == 0)
		return (error_and_free(NULL, NULL, 1,(*process)->child), i);
	return (i);
}

void	ft_export(t_process_list **process, t_env_var **env)
{
	int			i;
	char		*str_name;
	char		*str_value;
	t_env_var	*tmp;

	i = 0;
	str_name = NULL;
	str_value = NULL;
	tmp = *env;
	if ((*process)->argument[1] == NULL)
		return (ft_export_null((*env)));
	i = ft_find_equal(process);
	if (ft_isalpha((*process)->argument[1][0]) == 0)
		return (error_and_free(NULL, NULL, 1, (*process)->child));
	if ((*process)->argument[1][i] != '='
		&& ft_isalpha((*process)->argument[1][0]) == 0)
		return (error_and_free(NULL, NULL, 0, (*process)->child));
	str_name = ft_substr_lib((*process)->argument[1], 0, i);
	str_value = ft_substr_lib((*process)->argument[1], i + 1,
			ft_strlen_lib((*process)->argument[1]) - i + 1);
	if (ft_strchr(str_name, '-') != NULL || ft_isalpha(str_name[0]) == 0)
		return (error_and_free(NULL, NULL, 1, (*process)->child));
	ft_export_utility(tmp, str_name, str_value, env);
	g_status = 0;
}
