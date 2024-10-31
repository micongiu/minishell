#include "../minishell.h"

int init_readline(int argc , char **argv)
{
	int i = 0;
	const char *av = *argv;
	char *c;

	c = readline(av);
	printf("%s\n", c);
	free(c);
}

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

int	main(int argc, char **argv,char **env)
{
	t_rline *line;

	if (argc != 1)
		return (printf("Error argc number\n"), 1);
	line = ft_calloc(1, sizeof(t_rline));
	while (1)
	{
		signal(SIGINT, signal_handle);
		signal(SIGQUIT, SIG_IGN);
		free(line->input);
		line->input = readline("minishell->");
		if (line->input == NULL)
		{
			free(line->input);
			clear_history();
			printf("End of input\n");
			break ;
		}
		add_history(line->input);
		line->mat_input = ft_split(line->input, ' ');
	}
	return(0);
}
