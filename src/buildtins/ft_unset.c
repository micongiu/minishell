/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmedyns <anmedyns@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 16:05:51 by anmedyns          #+#    #+#             */
/*   Updated: 2025/01/03 15:39:21 by anmedyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	remove_env_node(t_env_var **env, t_env_var *prev, t_env_var *curr)
{
	if (prev)
		prev->next = curr->next;
	else
		*env = curr->next;
	free(curr->name);
	free(curr->value);
	free(curr);
}

void	ft_unset(t_env_var **env, char *str, int child)
{
	t_env_var	*prev;
	t_env_var	*curr;
	char		*new_str;

	if (!str)
		error_and_free(NULL, NULL, 0, child);
	new_str = remove_quotes(str);
	if (!new_str)
		error_and_free(NULL, NULL, 0, child);
	prev = NULL;
	curr = *env;
	while (curr)
	{
		if (ft_strncmp(new_str, curr->name, ft_strlen_lib(curr->name)) == 0)
		{
			remove_env_node(env, prev, curr);
			free(new_str);
			break ;
		}
		prev = curr;
		curr = curr->next;
	}
	g_status = 0;
}
