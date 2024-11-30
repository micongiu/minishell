#include"../minishell.h"

t_env_var *get_node_of(t_env_var **env_list, char *c)
{
	t_env_var *current;

	if (!env_list || !c)
		return NULL;
	current = *env_list;
	while (current)
	{
		if (ft_strncmp(current->name, c, ft_strlen_lib(c)) == 0)
			return current;
		current = current->next;
	}
	return NULL;
}


void change_directory(t_process_list *process, t_env_var **env_list)
{
	char *home_pwd;

	t_env_var *env = *env_list;
	env = get_node_of(env_list,"HOME");
	home_pwd = malloc(ft_strlen_lib(env->value) + 1);
	if(ft_strlcpy(home_pwd, env->value, ft_strlen_lib(env->value) == 0))
	{
	//	printf("home_pwd = %i\n", home_pwd);
		printf("Error change_dir strlcpy\n");
		return;
	}
	if(process->argument[1] == NULL)
	{
		if (chdir(env->value) != 0)
		{
			perror("cd");
			return;
		}
		env = get_node_of(env_list,"PWD");
		free(env->value);
		env->value = malloc(ft_strlen_lib(home_pwd) + 1);
		ft_strlcpy(env->value, home_pwd, ft_strlen_lib(home_pwd) == 0);
		printf("siamo a = %s\n", env->value);
	}
}


void execute_command(t_process_list *process,t_env_var **env_list)
{
	if(ft_strncmp(process->command, "cd", 3) == 0)
		change_directory(process,env_list);
}

