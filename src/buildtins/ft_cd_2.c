#include "../../minishell.h"

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
	env->value = ft_calloc(ft_strlen_lib(new_pwd) + 1, sizeof(char *));
	if (ft_strlcpy(env->value, new_pwd, ft_strlen_lib(new_pwd) + 1) == 0)
		printf("Error updating PWD\n");
}

void	execute_command(t_process_list *process, t_env_var **env_list,
		char **env_mat)
{
	char *c;

	c = "/bin/";
	if (ft_strncmp (process->command, "cd", 3) == 0)
		change_directory(process, env_list);
	else if (ft_strncmp (process->command, "pwd", 4) == 0)
		pwd_directory(env_list);
	else if (ft_strncmp (process->command, "echo", 5) == 0)
		ft_echo(process);
	else if (ft_strncmp (process->command, "env", 4) == 0)
		ft_env(*env_list, process->argument[1]);
	else if (ft_strncmp (process->command, "export", 7) == 0)
		ft_export(&process, env_list);
	else if (ft_strncmp (process->command, "unset", 6) == 0
		&& !(process->option))
		ft_unset(env_list, process->argument[1]);
	else if (ft_strncmp(process->command, "exit", 5) == 0)
		ft_exit(NULL, &*env_list, &process, env_mat);
	else
	{
		c = ft_strjoin_lib(c, process->argument[0]);
		execve(c , process->argument, env_mat);
		perror("Error executing command with execve");
		exit(EXIT_FAILURE);
	}
}
