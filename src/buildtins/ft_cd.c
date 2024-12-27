/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmedyns <anmedyns@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 16:06:29 by anmedyns          #+#    #+#             */
/*   Updated: 2024/12/27 16:06:31 by anmedyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	update_pwd(t_env_var *env, char *new_pwd)
{
	free(env->value);
	env->value = ft_strdup(new_pwd);
	if (!env->value)
		error_and_free("Error updating PWD\n", NULL, 1);
}

char	*get_home_directory(t_env_var **env_list)
{
	t_env_var	*env;

	env = get_node_of(env_list, "HOME");
	if (!env || !env->value)
		return (error_and_free("cd: HOME not set\n", NULL, 1), NULL);
	return (ft_strdup(env->value));
}

void	cd_parent_directory(t_env_var *env)
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
			("Error changing to parent directory\n", NULL, 1));
	update_pwd(env, parent);
	free(parent);
}

void	cd_specific_directory(t_process_list *process, t_env_var *env)
{
	char	*new_pwd;
	char	*path;

	path = process->argument[1];
	if (chdir(path) != 0)
		return (error_and_free("minishell: No such file or directory",
			NULL, 1));
	if (path[0] == '/')
		new_pwd = ft_strdup(path);
	else if (env->value[ft_strlen_lib (env->value) - 1] != '/')
		new_pwd = ft_strjoin_lib(ft_strjoin_lib (env->value, "/"), path);
	else
		new_pwd = ft_strjoin_lib (env->value, path);
	update_pwd(env, new_pwd);
	free(new_pwd);
}

void	ft_cd(t_process_list *process, t_env_var **env_list)
{
	t_env_var	*pwd_env;
	char		*home;
	t_env_var	*env;

	if (process->argument[2])
		return (error_and_free("minishell: too many arguments\n", NULL, 1));
	pwd_env = get_node_of(env_list, "PWD");
	if (!pwd_env)
		return (error_and_free("env_PWD not found\n", NULL, 1));
	if (!process->argument[1])
	{
		env = get_node_of(env_list, "HOME");
		if (!env || !env->value)
			return (error_and_free("cd: HOME not set\n", NULL, 1));
		home = (ft_strdup(env->value));
		if (!home || chdir(home) != 0)
			return (free(home), error_and_free("cd: HOME not set\n", NULL, 1));
		update_pwd(pwd_env, home);
		free(home);
	}
	else if (ft_strncmp(process->argument[1], "..", 3) == 0)
		cd_parent_directory(pwd_env);
	else if (ft_strncmp(process->argument[1], ".", 2) != 0)
		cd_specific_directory(process, pwd_env);
}
