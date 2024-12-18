#include "../minishell.h"

extern int	g_status;

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

void	*ft_error(int err_type, char *str, int err)
{
	g_status = err;
	if (err_type == 1)
		ft_putstr_fd("minishell: error while looking for matching quote\n", 2);
	else if (err_type == NDIR)
		ft_putstr_fd("minishell: No such file or directory: ", 2);
	else if (err_type == NPERM)
		ft_putstr_fd("minishell: permission denied: ", 2);
	else if (err_type == NCMD)
		ft_putstr_fd("minishell: command not found: ", 2);
	else if (err_type == DUPERR)
		ft_putstr_fd("minishell: dup2 failed\n", 2);
	else if (err_type == FORKERR)
		ft_putstr_fd("minishell: fork failed\n", 2);
	else if (err_type == PIPERR)
		ft_putstr_fd("minishell: error creating pipe\n", 2);
	else if (err_type == PIPENDERR)
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
	else if (err_type == MEM)
		ft_putstr_fd("minishell: no memory left on device\n", 2);
	else if (err_type == IS_DIR)
		ft_putstr_fd("minishell: Is a directory: ", 2);
	else if (err_type == NOT_DIR)
		ft_putstr_fd("minishell: Not a directory: ", 2);
	else if (err_type == NOT_FILE_OR_DIR)
		ft_putstr_fd("minishell: Not a directory: ", 2);
	ft_putendl_fd(str, 2);
	return (NULL);
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
		ft_execute_pipe_line(&env_list, head_process);
		free_matrix((void **) line->mat_input);
		free_process_list(&head_process);
	}
	free_env_list(&env_list);
}

// pwd ciao+
// pwd: too many arguments

// env gnl                                                     
// env: ‘gnl’: No such file or directory
// ➜  minishell git:(builtins) ✗ echo $?                                                     
// 127

// cd ciao
// cd: no such file or directory: ciao
// ➜  minishell git:(builtins) ✗ echo $?   
// 1

