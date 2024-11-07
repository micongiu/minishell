#include "../minishell.h"

void	signal_handle(int signal)
{
	if (signal == SIGINT)
	{
		// g_status = 130
		rl_replace_line("", 1);
		ft_putendl_fd("", STDOUT_FILENO);
		if (rl_on_new_line() == -1)
			exit (EXIT_FAILURE);
		rl_redisplay();
	}
}

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

void ft_ex_dollar(char **matrix, t_env_var *env)
{
	int	i;
	int	j;

	i = 0;
	while (env)
	{
		i = 0;
		while (matrix[i])
		{
			j = 0;
			while (matrix[i][j])
			{
				if (matrix[i][j] == '$')
					ft_check_str(matrix[i], env);
				j++;
			}
			i++;
		}
		env = env->next;
	}
}

int	main(int argc, char **argv,char **env)
{
	t_rline *line;
	int i = 0;
	int j = 0;
	char **environ;
	if (argc != 1)
		return (printf("Error argc number\n"), 1);
	line = ft_calloc(1, sizeof(t_rline));
	while (1)
	{
		t_env_var *env_list = NULL;
		signal(SIGINT, signal_handle);
		signal(SIGQUIT, SIG_IGN);
		free(line->input);
		init_env_list(&env_list, env);
		line->input = readline("minishell->");
		if (line->input == NULL)
		{
			free(line->input);
			free(line);
			free_env_list(&env_list);
			clear_history();
			printf("End of input\n");
			break ;
		}
		add_history(line->input);

		line->mat_input = ft_tokenizer(line->input, env_list);
		ft_ex_dollar(line->mat_input, env_list);

		i = 0;
		while (line->mat_input[i] != NULL)
		{
			printf("%s\n", line->mat_input[i]);
			i++;
		}
		free_matrix((void **)line->mat_input);
		free_env_list(&env_list);
	}
}
