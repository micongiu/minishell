#include "../minishell.h"

void	ft_check_str(char *str, t_env_var *env)
{
	int	i;
	int	j;
	int	tmp;
	int count;

	i = 0;
	j = -1;
	tmp = 0;
	count = 0;
	while (str[tmp] != '$')
		tmp++;
	i = tmp;
	while (str[++i] && env->name[++j])
	{
		if (str[i] == env->name[j])
			count++;
	}
	j = -1;
	tmp--;
	if (count == ft_strlen_lib(env->name))
	{
		while (env->value[++j])
			str[++tmp] = env->value[j];
	}
}

void ft_ex_dollar(char *matrix, t_env_var *env)
{
	int	i;
	int	j;

	i = 0;
	while (env)
	{
		j = 0;
		while (matrix[j])
		{
			if (matrix[j] == '$')
				ft_check_str(matrix, env);
			j++;
		}
		env = env->next;
	}
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

	i = 0;
	env_list = NULL;
	line = NULL;
	if (argc != 1)
		return (printf("Error argc number\n"), 1);
	line = ft_calloc(1, sizeof(t_rline));
	while (1)
	{
		env_list = NULL;
		signal(SIGINT, ft_signal_handle);
		signal(SIGQUIT, SIG_IGN);
		free(line->input);
		init_env_list(&env_list, env);
		line->input = readline("minishell->");
		if (line->input == NULL)
			return(ft_exit(line, &env_list), 0);
		add_history(line->input);
		line->mat_input = ft_tokenizer(line->input, env_list);
		i = 0;
		while (line->mat_input[i] != NULL)
			printf("%s\n", line->mat_input[i++]);
		free_matrix((void **)line->mat_input);
		free_env_list(&env_list);
	}
}
