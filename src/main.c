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

void	ft_exit(t_rline *line, t_env_var **env_list, t_process_list **head_process)
{
	free(line->input);
	free(line);
	free_env_list(env_list);
	free_process_list(head_process);
	clear_history();
	printf("exit\n");
}

void	ft_env(t_env_var **env)
{
	while (*env != NULL)
	{
		// if ((*env)->name && (*env)->value)
		printf("%s=%s\n", (*env)->name, (*env)->value);
		(*env) = (*env)->next;
	}
}

void	ft_unset(t_env_var **env, char *str)
{
	t_env_var *prev;
	t_env_var *curr;

	prev = NULL;
	curr = *env;
	while (curr)
	{
		if (ft_strncmp(str, curr->name, ft_strlen_lib(curr->name)) == 0)
		{
			if (prev)
				prev->next = curr->next;
			else
				*env = curr->next;
			free(curr->name);
			free(curr->value);
			free(curr);
			break;
		}
		prev = curr;
		curr = curr->next;
	}
}

int	main(int argc, char **argv,char **env)
{
	t_rline	*line;
	t_env_var *env_list;
	t_process_list *head_process;

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
			return(ft_exit(line, &env_list, &head_process), 0);
		line->mat_input = ft_tokenizer(line->input, env_list);
		head_process = ft_init_process_list(line->mat_input);
		add_history(line->input);
		if(line->mat_input[0])
			execute_command(head_process,&env_list);
		free_matrix((void **)line->mat_input);
		free_env_list(&env_list);
		free_process_list(&head_process);
		free_process_list(&head_process);
	}
}


// se trovo << , dichiari stringa cacca = "comadno1 \n , comando2 \n, comando3 \n"


