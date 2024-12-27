#include "../minishell.h"

char	get_first_quote(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '\"')
			return (str[i]);
		i++;
	}
	return (0);
}

char	*remove_quotes(char *str)
{
	int		i;
	int		j;
	char	*new_str;
	char	quote_type;

	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	quote_type = get_first_quote(str);
	new_str = ft_calloc((ft_strlen_lib(str) + 1), sizeof(char));
	if (!new_str)
		return (NULL);
	while (str[i] != '\0')
	{
		if (str[i] != quote_type)
			new_str[j++] = str[i];
		i++;
	}
	new_str[j] = '\0';
	return (new_str);
}


t_var_count	ft_ex_dollar(char *line, char *token,
	t_env_var *env, t_var_count count)
{
	int	j;
	int	k;
	int	tmp;

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
	if (count.i == 0)
		count.i++;
	return (count);
}

int	main(int argc, char **argv, char **env)
{
	char			*input;
	t_env_var		*env_list;
	t_process_list	*head_process;

	env_list = NULL;
	head_process = NULL;
	input = NULL;
	env_list = NULL;
	if (argc != 1 && argv[0] == NULL)
		return (printf("Error argc number\n"), 1);
	ft_init_env_list(&env_list, env);
	while (1)
	{
		head_process = NULL;
		signal(SIGINT, ft_signal_handle);
		signal(SIGQUIT, SIG_IGN);
		input = readline("minishell->");
		if (input == NULL)
			return (ft_exit(input, &env_list, &head_process, NULL), 0);
		if (ft_strlen_lib(input) > 0)
		{
			add_history(input);
			head_process = ft_init_process_list(ft_tokenizer(input, env_list));
			ft_execute_pipe_line(&env_list, head_process);
		}
		if(head_process)
			free_process_list(&head_process);
	}
}
