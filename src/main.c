#include "../minishell.h"

int	g_status;

int init_readline(int argc , char **argv)
{
	int i = 0;
	const char *av = *argv;
	char *c;
	c = readline(av);
	printf("%s\n", c);
}

void	signal_handle(int signal)
{
	if (signal == SIGINT)
	{
		g_status = 130;
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

int	main(int argc, char **argv)
{
	while (1)
	{

		signal(SIGINT, signal_handle);
		signal(SIGQUIT, SIG_IGN);
		//readline
		if(init_readline(argc, argv));
			printf("error init_readline\n");
		//parser
		//exec(exit)
		//exit
	}
}
