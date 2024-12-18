#include "../minishell.h"

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

void	cd_home_directory(t_env_var **env_list, t_env_var *env)
{
	char	*home;

	home = get_home_directory (env_list);
	if (!home)
		return ;
	if (chdir (home) != 0)
	{
		printf ("Error changing to home directory\n");
		free (home);
		return ;
	}
	update_pwd (env, home);
	free (home);
}

void	cd_parent_directory(t_env_var **env_list, t_env_var *env)
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

void	cd_specific_directory(t_process_list *process,
	t_env_var **env_list, t_env_var *env)
{
	char	*temp;
	char	*new_pwd;
	char	*path;

	temp = NULL;
	new_pwd = NULL;
	path = process->argument[1];
	if (chdir(path) != 0)
	{
		printf("Error changing to specific path: %s\n", path);
		return ;
	}
	if (process->argument[1][0] == '/')
		new_pwd = process->argument[1];
	if (env->value[ft_strlen_lib (env->value) - 1] != '/')
	{
		temp = ft_strjoin_lib (env->value, "/");
		new_pwd = ft_strjoin_lib (temp, path);
		free (temp);
	}
	else
		new_pwd = ft_strjoin_lib (env->value, path);
	update_pwd (env, new_pwd);
	free (new_pwd);
}

void	change_directory(t_process_list *process, t_env_var **env_list)
{
	t_env_var	*pwd_env;

	pwd_env = get_node_of (env_list, "PWD");
	if (!pwd_env)
	{
		printf ("env_PWD not found\n");
		return ;
	}
	if (!process->argument[1])
		cd_home_directory (env_list, pwd_env);
	else if (ft_strncmp (process->argument[1], ".", 2) == 0)
		return ;
	else if (ft_strncmp (process->argument[1], "..", 3) == 0)
		cd_parent_directory (env_list, pwd_env);
	else
		cd_specific_directory (process, env_list, pwd_env);
}
