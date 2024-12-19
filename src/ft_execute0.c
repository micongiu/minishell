#include "../minishell.h"

t_env_var	*get_node_of(t_env_var **env_list, char *c)
{
	t_env_var	*current;

	if (!env_list || !c)
		return (NULL);
	current = *env_list;
	while (current)
	{
		if (ft_strncmp(current->name, c, ft_strlen_lib(c)) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}

void	update_pwd(t_env_var *env, char *new_pwd)
{
	free(env->value);
	env->value = malloc(ft_strlen_lib(new_pwd) + 1);
	if (ft_strlcpy(env->value, new_pwd, ft_strlen_lib(new_pwd) + 1) == 0)
		printf("Error updating PWD\n");
}

char	*get_home_directory(t_env_var **env_list)
{
	t_env_var	*env;
	char		*home;

	env = get_node_of(env_list, "HOME");
	home = malloc(ft_strlen_lib(env->value) + 1);
	if (!env || !env->value)
	{
		printf("Error: HOME not found\n");
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

void	pwd_directory(t_process_list *process, t_env_var **env_list, int fd)
{
	t_env_var	*env;

	env = *env_list;
	env = get_node_of(env_list, "PWD");
	ft_putendl_fd(env->value, fd);
}

void	execute_command(t_process_list *process, t_env_var **env_list,
		char **env_mat)
{
	if (ft_strncmp (process->command, "cd", 3) == 0)
		change_directory(process, env_list);
	else if (ft_strncmp (process->command, "pwd", 4) == 0)
		pwd_directory(process, env_list, process->fd);
	else if (ft_strncmp (process->command, "echo", 5) == 0)
		ft_echo(process, process->fd);
	else if (ft_strncmp (process->command, "env", 4) == 0)
		ft_env(*env_list, process->fd, process->argument[1]);
	else if (ft_strncmp (process->command, "export", 7) == 0)
		ft_export(&process, env_list, process->fd);
	else if (ft_strncmp (process->command, "unset", 6) == 0
		&& !(process->option))
		ft_unset(env_list, process->argument[1]);
	else
	{
		execve(process->argument[0], process->argument, env_mat);
		perror("Error executing command with execve");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
