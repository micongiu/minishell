#include "../minishell.h"

t_var_count	ft_ex_dollar(char *line, char *token,
	t_env_var *env, t_var_count count)
{
	int	j;
	int	k;
	int	tmp;

	k = 0;
	k = (ft_strchr(line, '$') - line);
	while (line && *line != '$')
		line++;
	line++;
	while (env)
	{
		j = 0;
		tmp = count.j;
		if (ft_strncmp(line, env->name, ft_strlen_lib(env->name)) == 0)
		{
			while (env->value[j])
				token[tmp++] = env->value[j++];
			count.i += k + ft_strlen_lib(env->name) + 1;
			count.j += tmp;
			break ;
		}
		env = env->next;
	}
	return (count);
}

void	ft_exit(t_rline *line, t_env_var **env_list,
	t_process_list **head_process)
{
	free(line->input);
	free(line);
	free_env_list(env_list);
	free_process_list(head_process);
	clear_history();
	printf("exit\n");
}

int	main(int argc, char **argv, char **env)
{
	t_rline			*line;
	t_env_var		*env_list;
	t_process_list	*head_process;

	env_list = NULL;
	head_process = NULL;
	line = NULL;
	if (argc != 1)
		return (printf("Error argc number\n"), 1);
	line = ft_calloc(1, sizeof(t_rline));
	env_list = NULL;
	ft_init_env_list(&env_list, env);
	while (1)
	{
		head_process = NULL;
		signal(SIGINT, ft_signal_handle);
		signal(SIGQUIT, SIG_IGN);
		free(line->input);
		line->input = readline("minishell->");
		if (line->input == NULL)
			return (ft_exit(line, &env_list, &head_process), 0);
		line->mat_input = ft_tokenizer(line->input, env_list);
		head_process = ft_init_process_list(line->mat_input);
		if (ft_strlen_lib(line->input) > 0)
			add_history(line->input);
		if (line->mat_input[0])
			execute_command(head_process, &env_list);
		free_matrix((void **) line->mat_input);
		free_process_list(&head_process);
	}
	free_env_list(&env_list);
}
