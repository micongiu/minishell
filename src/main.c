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

// print all the env_list, questa leaka GESÙ

void	ft_env(t_env_var *env)
{
    t_env_var *current;

	current = env;
    while (current != NULL)
	{
        printf("%s=%s\n", current->name, current->value);
        current = current->next;
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

void	ft_export(t_process_list **info_process, t_env_var **env)
{
	int		i;
	char	*str_name;
	char	*str_value;

	i = 0;
	str_name = NULL;
	str_value = NULL;
	while ((*info_process)->argument[1][i] && (*info_process)->argument[1][i] != '=')
		i++;
	if ((*info_process)->argument[1][i] != '=')
		return ;
	str_name = ft_substr_lib((*info_process)->argument[1], 0, i);
	str_value = ft_substr_lib((*info_process)->argument[1], i + 1, ft_strlen_lib((*info_process)->argument[1]) - i + 1);
	while (*env)
	{
		if (ft_strncmp(str_name, (*env)->name, ft_strlen_lib((*env)->name)) == 0)
		{
			free((*env)->value);
			(*env)->value = ft_strdup_lib(str_value);
			free(str_value);
			return (free(str_name));
		}
		*env = (*env)->next;
	}
	ft_add_env_var(env, ft_create_env_node(str_name, str_value));
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
		free_matrix((void **)line->mat_input);
		free_env_list(&env_list);
		free_process_list(&head_process);
		free_process_list(&head_process);
	}
}


// se trovo << , dichiari stringa cacca = "comadno1 \n , comando2 \n, comando3 \n"


