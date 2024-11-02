#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/wait.h>
# include <limits.h>
# include <errno.h>
# include <signal.h>
# include <sys/ioctl.h>
# include <readline/readline.h>
# include <readline/history.h>

//servono per il tokenizer , anziche contare quanti token sono , noi ci teniamo larghi tanto sti cazzi daje
#define MAX_TOKENS 100
#define MAX_TOKEN_LEN 50


typedef struct s_rline
{
	char *input;
	char **mat_input;
}	t_rline;

int	main(int argc, char **argv,char **env);


#endif
