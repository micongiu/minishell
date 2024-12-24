#include "../../minishell.h"

char	*compute_parent_directory(char *pwd)
{
	int		len;
	char	*parent;

	len = ft_strlen_lib(pwd);
	if (len > 1)
		len -= 2;
	while (len > 0 && pwd[len] != '/')
		len--;
	if (len == 0)
		len = 1;
	parent = malloc(len + 1);
	if (!parent || ft_strlcpy(parent, pwd, len + 1) == 0)
	{
		printf("Error computing parent directory\n");
		free(parent);
		return (NULL);
	}
	return (parent);
}

char	*get_home_directory(t_env_var **env_list)
{
	t_env_var	*env;
	char		*home;

	env = get_node_of(env_list, "HOME");
	home = malloc(ft_strlen_lib(env->value) + 1);
	if (!env || !env->value)
	{
		ft_error(16, NULL, 1);
		return (NULL);
	}
	if (!home || ft_strlcpy(home, env->value, ft_strlen_lib(env->value) + 1)
		== 0)
	{
		printf("Error copying HOME\n");
		free(home);
		return (NULL);
	}
	return (home);
}

void	cd_parent_directory(t_env_var *env)
{
	char	*parent;

	parent = compute_parent_directory(env->value);
	if (!parent)
		return ;
	if (chdir("..") != 0)
	{
		printf ("Error changing to parent directory\n");
		free (parent);
		return ;
	}
	update_pwd (env, parent);
	free (parent);
}

void	cd_specific_directory(t_process_list *process, t_env_var *env)
{
	char	*new_pwd;
	char	*path;

	new_pwd = NULL;
	path = process->argument[1];
	if (chdir(path) != 0)
	{
		ft_error(2, path, 1);
		return ;
	}
	if (process->argument[1][0] == '/')
		new_pwd = process->argument[1];
	else if(env->value[ft_strlen_lib (env->value) - 1] != '/')
	{
		new_pwd = ft_strjoin_lib (ft_strjoin_lib (env->value, "/"), path);
	}
	else
		new_pwd = ft_strjoin_lib (env->value, path);
	update_pwd (env, new_pwd);
}

void	change_directory(t_process_list *process, t_env_var **env_list)
{
	t_env_var	*pwd_env;
	char		*home;

	if (process->argument[2])
		return (ft_error(15, process->command, 1));
	pwd_env = get_node_of(env_list, "PWD");
	if (!pwd_env)
		ft_error(17, NULL, 126);
	if (!process->argument[1])
	{
		home = get_home_directory (env_list);
		if (!home)
			return ;
		if (chdir (home) != 0)
			return (free(home), ft_error(16, NULL, 126));
		update_pwd(pwd_env, home);
		free(home);
	}
	else if (ft_strncmp (process->argument[1], ".", 2) == 0)
		return ;
	else if (ft_strncmp (process->argument[1], "..", 3) == 0)
		cd_parent_directory (pwd_env);
	else
		cd_specific_directory (process, pwd_env);
}
