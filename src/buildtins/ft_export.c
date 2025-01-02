/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmedyns <anmedyns@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 16:05:22 by anmedyns          #+#    #+#             */
/*   Updated: 2025/01/02 20:47:27 by anmedyns         ###   ########.fr       */
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

void	ft_export(t_process_list **info_process, t_env_var **env)
{
	int			i;
	char		*str_name;
	char		*str_value;
	t_env_var	*tmp;

	i = 0;
	str_name = NULL;
	str_value = NULL;
	tmp = *env;
	if ((*info_process)->argument[1] == NULL)
	{
		ft_export_null((*env));
		return ;
	}
	while ((*info_process)->argument[1][i]
			&& (*info_process)->argument[1][i] != '=')
		i++;
	if ((*info_process)->argument[1][i] != '=')
		return ;
	str_name = ft_substr_lib((*info_process)->argument[1], 0, i);
	str_value = ft_substr_lib((*info_process)->argument[1], i + 1,
			ft_strlen_lib((*info_process)->argument[1]) - i + 1);
	ft_export_utility(tmp, str_name, str_value, env);
	g_status = 0;
}
