#include "../minishell.h"

int	g_status;

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
		rl_replace_line("", 1);
		ft_putendl_fd("", STDOUT_FILENO);
		if (rl_on_new_line() == -1)
			exit (EXIT_FAILURE);
		rl_redisplay();
	}
}

int main(int argc, char **argv)
{
    char *line;

    while ((line = readline("> ")) != NULL)
	{
		signal(SIGINT, signal_handle);
		signal(SIGQUIT, SIG_IGN);
        printf("You entered: %s\n", line);
        add_history(line);
        free(line);
    }
	clear_history();
    printf("End of input\n");
    return 0;
}
