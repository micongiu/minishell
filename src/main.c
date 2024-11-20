#include "../minishell.h"

t_var_count	ft_check_str(char *line, char *token, t_env_var *env, t_var_count count)
{
	int	j;
	int k;
	int	tmp;

	j = 0;
	k = 0;
	tmp = count.i;
	count.i++;
	while (line[count.i] && env->name[j])
	{
		if (line[count.i] == env->name[j])
			k++;
		count.i++;
		j++;
	}
	j = 0;
	if (k == ft_strlen_lib(env->name))
	{
		while (env->value[j++])
			token[tmp++] = env->value[j];
		count.i =+ k - 1;
		count.j =+ tmp;
	}
	return (count);
}

t_var_count ft_ex_dollar(char *line, char *token, t_env_var *env, t_var_count count)
{
	while (env)
	{
		count = ft_check_str(line, token, env, count);
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
		while (line->mat_input[i] != NULL)
			printf("%s\n", line->mat_input[i++]);
		free_matrix((void **)line->mat_input);
		free_env_list(&env_list);
		free_process_list(&head_process);
	}
}
