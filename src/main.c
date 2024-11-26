#include "../minishell.h"

t_var_count ft_ex_dollar(char *line, char *token, t_env_var *env, t_var_count count)
{
	int	j;
	int k;
	int	tmp;

	k = 0;
	while (line && *line != '$')
		line++;
	line++;
	k = *line;
	while (env)
	{
		j = 0;
		tmp = count.j;
		if (ft_strncmp(line, env->name, ft_strlen_lib(env->name)) == 0)
		{
			while (env->value[j])
				token[tmp++] = env->value[j++];
			count.i =+ k + ft_strlen_lib(env->name);
			count.j =+ tmp;
			break ;
		}
		env = env->next;
	}
	return (count);
}

void	ft_exit(t_rline *line, t_env_var **env_list)
{
	free(line->input);
	free(line);
	free_env_list(env_list);
	clear_history();
	printf("exit\n");
}

// print all the env_list

void	ft_env(t_env_var **env)
{
	while (env)
	{
		printf("%s=%s\n", (*env)->name, (*env)->value);
		(*env) = (*env)->next;
	}
}

void	ft_unset(t_env_var **env, char *str)
{
	t_env_var *env_tmp;

	env_tmp	= (*env);
	while (env)
	{
		if (ft_strncmp(str, (*env)->name, ft_strlen_lib((*env)->name)) == 0)
		{
			env_tmp = (*env)->next;
			free((*env)->name);
			free((*env)->value);
			free((*env));
			*env = env_tmp;
			break ;
		}
		(*env) = (*env)->next;
	}
}

int	main(int argc, char **argv,char **env)
{
	t_rline	*line;
	int 	i;
	t_env_var *env_list;
	t_process_list *head_process;


	i = 0;
	env_list = NULL;
	head_process = NULL;
	line = NULL;
	if (argc != 1)
		return (printf("Error argc number\n"), 1);
	line = ft_calloc(1, sizeof(t_rline));
	while (1)
	{
		env_list = NULL;
		head_process = NULL;
		signal(SIGINT, ft_signal_handle);
		signal(SIGQUIT, SIG_IGN);
		free(line->input);
		ft_init_env_list(&env_list, env);
		line->input = readline("minishell->");
		if (line->input == NULL)
			return(ft_exit(line, &env_list), 0);
		add_history(line->input);
		line->mat_input = ft_tokenizer(line->input, env_list);
		i = 0;
		head_process = ft_init_process_list(line->mat_input);
		// while (line->mat_input[i] != NULL)
		// 	printf("%s\n", line->mat_input[i++]);
		ft_unset(&env_list, "PATH");
		// ft_env(&env_list);
		free_matrix((void **)line->mat_input);
		free_env_list(&env_list);
		free_process_list(&head_process);
	}
}


// se trovo << , dichiari stringa cacca = "comadno1 \n , comando2 \n, comando3 \n"


