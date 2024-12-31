/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utility.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: micongiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 16:01:37 by micongiu          #+#    #+#             */
/*   Updated: 2024/12/27 16:01:39 by micongiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_status;

void	free_matrix(void **matrix)
{
	size_t	i;

	i = 0;
	if (matrix == NULL)
		return ;
	while (matrix[i])
	{
		free(matrix[i]);
		matrix[i] = NULL;
		i++;
	}
	free(matrix);
}

int	ft_count_node(t_env_var *env)
{
	int	i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

char	**ft_list_to_arr(t_env_var *env_h)
{
	char		**env_mat;
	int			i;
	char		*tmp;
	t_env_var	*current;

	current = env_h;
	i = 0;
	env_mat = ft_calloc((ft_count_node(current) + 1), sizeof(char *));
	while (current != NULL)
	{
		tmp = ft_strjoin_lib(current->name, "=");
		env_mat[i] = ft_strjoin_lib(tmp, current->value);
		free(tmp);
		i++;
		current = current->next;
	}
	return (env_mat);
}

int	is_builtins(char *str)
{
	return ((ft_strncmp(str, "cd", 3) == 0)
		|| (ft_strncmp(str, "pwd", 4) == 0)
		|| (ft_strncmp(str, "echo", 5) == 0)
		|| (ft_strncmp(str, "env", 4) == 0)
		|| (ft_strncmp(str, "export", 7) == 0)
		|| (ft_strncmp(str, "unset", 6) == 0)
		|| (ft_strncmp(str, "exit", 5) == 0)
		|| (ft_strncmp(str, "$?", 3) == 0));
}

void	error_and_free(char *str, char **env_mat, int status)
{
	perror(str);
	g_status = status;
	if (env_mat)
		free_matrix((void **)env_mat);
	exit(EXIT_FAILURE);
}
