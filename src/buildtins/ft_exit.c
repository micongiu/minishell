/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmedyns <anmedyns@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 16:06:03 by anmedyns          #+#    #+#             */
/*   Updated: 2025/01/03 15:06:28 by anmedyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_exit(char *str)
{
	int	o;

	o = 0;
	while (str[o])
	{
		if (ft_isalpha(str[o]) == 0)
			o++;
		else
			return (1);
	}
	return (0);
}

void	free_resources(char *line, t_env_var **env_list,
	t_process_list **head_process, char **env_mat)
{
	if (line)
		free(line);
	if (env_list)
		free_env_list(env_list);
	if (head_process)
		free_process_list(head_process);
	if (env_mat)
		free_matrix((void *)env_mat);
}

void	ft_exit(char *line, t_env_var **env_list,
	t_process_list **head_process, char **env_mat)
{
	int	result;
	int	exit_code;

	result = 0;
	if (head_process && *head_process && (*head_process)->argument[1])
	{
		if (!(*head_process)->argument[2])
		{
			if (check_exit((*head_process)->argument[1]) == 1)
				result = 2;
			else
			{
				exit_code = ft_atoi((*head_process)->argument[1]);
				while (exit_code > 256)
					exit_code -= 256;
				result = exit_code;
			}
		}
		else
			result = 1;
	}
	free_resources(line, env_list, head_process, env_mat);
	printf("exit\n");
	exit(result);
}
