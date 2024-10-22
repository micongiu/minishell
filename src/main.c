#include "../minishell.h"

int	main(int argc, char **argv, char **env)
{
    char *pwd;
	int		i = 0;

    pwd = getcwd(NULL, 0);
    printf("pwd: %s\n", pwd);
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
    return (0);
}
