/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmedyns <anmedyns@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 16:05:42 by anmedyns          #+#    #+#             */
/*   Updated: 2025/01/02 20:46:50 by anmedyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_pwd(t_env_var **env_list)
{
	t_env_var	*env;

	env = *env_list;
	env = get_node_of(env_list, "PWD");
	ft_putendl_fd(env->value, STDOUT_FILENO);
	g_status = 0;
}
