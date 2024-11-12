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

typedef struct s_env_var
{
	char			*name;
	char			*value;
	struct s_env_var *next;
}	t_env_var;

typedef struct s_rline
{
	char	*input;
	char	**mat_input;
}	t_rline;


typedef struct s_var_count
{
	int	i;
	int	j;
	int	k;
}	t_var_count;

// main.c

int			main(int argc, char **argv,char **env);
t_var_count	ft_ex_dollar(char *line, char *token, t_env_var *env, t_var_count count);

// ft_env.c

void		ft_init_env_list(t_env_var **env_list, char **env);
void 		free_env_list(t_env_var **cur);


// ft_tokenizer.c

char		**ft_tokenizer(char *input, t_env_var *env);

// ft_tokenizer_utility.c

int			is_space(char c);
int			ft_check_quote(char *input);
int			ft_count(char *input, int i);
int			ft_count_token(char *input);

// ft_signal_handle.c

void		ft_signal_handle(int signal);

// ft_utility.c

void		free_matrix(void **matrix);

#endif
