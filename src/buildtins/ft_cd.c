/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmedyns <anmedyns@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 16:06:29 by anmedyns          #+#    #+#             */
/*   Updated: 2025/01/03 15:49:26 by anmedyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	update_pwd(t_env_var *env, char *new_pwd, int child)
{
	free(env->value);
	env->value = ft_strdup(new_pwd);
	if (!env->value)
		error_and_free("Error updating PWD\n", NULL, 1, child);
}

// This function returns the HOME directory from
// the list of environment variables.
char	*get_home_directory(t_env_var **env_list, int child)
{
	t_env_var	*env;

	env = get_node_of(env_list, "HOME");
	if (!env || !env->value)
		return (error_and_free("cd: HOME not set", NULL, 1, child), NULL);
	return (ft_strdup(env->value));
}

// This function changes the current
// directory to the parent directory.
void	cd_parent_directory(t_env_var *env, int child)
{
	char	*parent;
	int		len;

	len = ft_strlen_lib(env->value);
	while (len > 1 && env->value[len - 1] == '/')
		len--;
	while (len > 0 && env->value[len - 1] != '/')
		len--;
	if (len == 0)
		len = 1;
	parent = ft_substr_lib(env->value, 0, len);
	if (!parent || chdir(parent) != 0)
		return (free(parent), error_and_free
			("Error changing to parent directory\n", NULL, 1, child));
	update_pwd(env, parent, child);
	free(parent);
}

// This function changes the current directory
// to a specific directory provided in the arguments.
void	cd_specific_directory(t_process_list *process, t_env_var *env)
{
	char	*new_pwd;
	char	*path;

	path = process->argument[1];
	if (chdir(path) != 0)
	{
		error_and_free ("minishell", NULL, 1, process->child);
		return ;
	}
	if (path[0] == '/')
		new_pwd = ft_strdup(path);
	else if (env->value[ft_strlen_lib (env->value) - 1] != '/')
		new_pwd = ft_strjoin_lib(ft_strjoin_lib (env->value, "/"), path);
	else
		new_pwd = ft_strjoin_lib (env->value, path);
	update_pwd(env, new_pwd, process->child);
	free(new_pwd);
	g_status = 0;
}

// This function handles the "cd" command,
// managing arguments and special cases like HOME or "..".
void	ft_cd(t_process_list *p, t_env_var **env_list)
{
	t_env_var	*pwd_env;
	char		*home;
	t_env_var	*env;

	if (p->argument[2])
		return (error_and_free("cd: Too many arguments\n", NULL, 1, p->child));
	pwd_env = get_node_of(env_list, "PWD");
	if (!pwd_env)
		return (error_and_free("envPWD not found\n", NULL, 1, p->child));
	if (!p->argument[1])
	{
		env = get_node_of(env_list, "HOME");
		if (!env || !env->value)
			return (error_and_free("cd: HOME not set\n", NULL, 1, p->child));
		home = (ft_strdup(env->value));
		if (!home || chdir(home) != 0)
			return (free(home),
				error_and_free("cd: HOME not set\n", NULL, 1, p->child));
		update_pwd(pwd_env, home, p->child);
		free(home);
	}
	else if (ft_strncmp(p->argument[1], "..", 3) == 0)
		cd_parent_directory(pwd_env, p->child);
	else if (ft_strncmp(p->argument[1], ".", 2) != 0)
		cd_specific_directory(p, pwd_env);
}
