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
	int len;

	t_env_var *env = get_node_of(env_list,"HOME");
	if(!process)
		return;
	home_pwd = malloc(ft_strlen_lib(env->value) + 1);
	if(ft_strlcpy(home_pwd, env->value, ft_strlen_lib(env->value)) == 0)
	{
		printf("Error change_dir strlcpy\n");
		free(home_pwd);
		return;
	}
	if(process->argument[1] == NULL)
	{
		// if(!env->value[1])
		// 	printf("PALLE SCURE\n");
		if (chdir(env->value) != 0)
		{
			printf("error_cd\n");
			return;
		}
		env = get_node_of(env_list,"PWD");
		free(env->value);
		env->value = malloc(ft_strlen_lib(home_pwd) + 2);
		if(ft_strlcpy(env->value, home_pwd, ft_strlen_lib(home_pwd) + 2) == 0)
		{
			printf("Error replace PWD strlcpy in cd\n");
			return;
		}
		//printf("dovrebbe essere PWD nuovo = %s\n", env->value);
	}
	else if(ft_strncmp(process->argument[1], ".", 2) == 0)
	{
		free(home_pwd);
		return;
	}
	else if(ft_strncmp(process->argument[1], "..", 3) == 0)
	{
		env = get_node_of(env_list,"PWD");
		len = ft_strlen_lib(env->value);
		while(env->value[len] != '/')
		{
			len--;
		}
		// if(len == 0)
		// 	printf("%spalle\n", env->value);
		if (chdir(process->argument[1]) != 0)
		{

			printf("error_cd\n");
			return;
		}
		if(len == 0)
			len = 1;
		free(home_pwd);
		home_pwd = malloc(len + 1);
		if(ft_strlcpy(home_pwd, env->value, len + 1) == 0)
		{
			printf("error strcpy in cd ..\n");
			return;
		}
		free(env->value);
		env->value = malloc(len + 1);
		len = ft_strlcpy(env->value, home_pwd, len + 1);
		free(home_pwd);
		printf("dovrebbe essere PWD nuovo = %s\n", env->value);
	}
	else
	{

		free(home_pwd);

		if(chdir(process->argument[1]) != 0)
		{
			printf("error_cd_path\n");
		}
		env = get_node_of(env_list,"PWD");
		if(!((env->value[ft_strlen_lib(env->value)]) == '/'))
		{
			home_pwd = ft_strjoin_lib(env->value, "/");
			home_pwd = ft_strjoin_lib(home_pwd,process->argument[1]);
		}
		else
		{
			home_pwd = ft_strjoin_lib(env->value, process->argument[1]);
		//	printf("home_pwd = %s\n", home_pwd);
		}

		free(env->value);
		env->value = malloc(ft_strlen_lib(home_pwd));
		if(ft_strlcpy(env->value, home_pwd, ft_strlen_lib(home_pwd) + 1) == 0)
		{
			printf("Error replace PWD strlcpy in cd_path\n");
			return;
		}
		//printf("dovrebbe essere PWD cd_path = %s\n", env->value);
	}
	env = get_node_of(env_list, "SHELL");
}

void pwd_directory(t_process_list *process, t_env_var **env_list)
{
	t_env_var *env = *env_list;
	env = get_node_of(env_list, "PWD");
	printf("%s\n", env->value);
}

void execute_command(t_process_list *process,t_env_var **env_list)
{
	if(ft_strncmp(process->command, "cd", 3) == 0)
		change_directory(process,env_list);
	else if (ft_strncmp(process->command, "pwd", 4) == 0)
		pwd_directory(process,env_list);
}

