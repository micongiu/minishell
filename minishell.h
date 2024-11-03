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


typedef struct s_env_var {
	char *name;
	char *value;
	struct s_env_var *next;
}	t_env_var;

typedef struct s_rline
{
	char *input;
	char **mat_input;
}	t_rline;

int	main(int argc, char **argv,char **env);
void env_storage(char **environ, t_env_var **list);
void free_env_list(t_env_var *env_list);
void init_env_list(t_env_var **env_list);
void add_env_var(t_env_var **env_list, t_env_var *new_var);
t_env_var *create_env_node(const char *name, const char *value);
char *my_strndup(const char *s, size_t n);
int ft_strnlen(const char *str, char n);


#endif
