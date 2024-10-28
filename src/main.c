#include "../minishell.h"


int init_readline(int argc , char **argv)
{
	int i = 0;
	const char *av = *argv;
	char *c;
	c = readline(av);
	printf("%s\n", c);
}

int	main(int argc, char **argv)
{
	while (1)
	{

		//signal
		//readline
		if(init_readline(argc, argv));
			printf("error init_readline\n");
		//parser
		//exec(exit)
		//exit
	}
}
