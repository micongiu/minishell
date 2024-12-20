#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include "gnl/get_next_line.h"
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
	char				*name;
	char				*value;
	struct s_env_var	*next;
}	t_env_var;

typedef struct s_process_list
{
	char					*command;
	char					*option;
	char					*file_fd;
	int						fd;
	int						redirection;
	char					*full_process;
	char					**argument;
	struct s_process_list	*next;
}	t_process_list;

// REDIRECTION _________1 = 1 ; 2 = 2;  3 = 1 inversa  , 4  = 2 inversse

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

enum	e_error
{
	QUOTE = 1,
	NDIR = 2,
	NPERM = 3,
	NCMD = 6,
	DUPERR = 7,
	FORKERR = 8,
	PIPERR = 9,
	PIPENDERR = 10,
	MEM = 11,
	IS_DIR = 12,
	NOT_DIR = 13,
	NOT_FILE_OR_DIR = 14,
	TOO_MUCH_DIR = 15,
	HOME_DIRERR = 16,
	NENV_PWD = 17
};

enum	e_redirection
{
	S_IN_RED = 1,
	S_OUT_RED = 2,
	HERDOC = 3,
	D_OUT_RED = 4
};

// main.c

char			*remove_quotes(char *str);
void			ft_error(int err_type, char *str, int err);
int				main(int argc, char **argv, char **env);
t_var_count		ft_ex_dollar(char *line, char *token, t_env_var *env,
					t_var_count count);

// ft_env.c

t_env_var		*ft_create_env_node(char *name, char *value);
void			ft_add_env_var(t_env_var **env_list, t_env_var *new_var);
void			ft_init_env_list(t_env_var **env_list, char **env);
void			free_env_list(t_env_var **cur);

// ft_tokenizer.c

char			**ft_tokenizer(char *input, t_env_var *env);

// ft_tokenizer_utility.c

int				is_space(char c);
int				ft_check_quote(char *input);

// ft_tokenizer_counter.c

int				ft_count(char *input, int i, t_env_var *env);
int				ft_count_token(char *input);

// ft_signal_handle.c

void			ft_signal_handle(int signal);

// ft_utility.c

void			free_matrix(void **matrix);

// ft_process.c

t_process_list	*ft_init_process_list(char **mat);
void			free_process_list(t_process_list **cur);
t_process_list	*ft_create_process_node(char **tokens);

//ft_execute.c

void			execute_command(t_process_list *process, t_env_var **env_list,
					char **env_mat);
void			pwd_directory(t_env_var **env_list, int fd);
char			*get_home_directory(t_env_var **env_list);
void			update_pwd(t_env_var *env, char *new_pwd);
t_env_var		*get_node_of(t_env_var **env_list, char *c);
void			change_directory(t_process_list *process, t_env_var **env_list);
void			cd_specific_directory(t_process_list *process, t_env_var *env);
void			cd_parent_directory(t_env_var *env);
void			cd_home_directory(t_env_var **env_list, t_env_var *env);
char			*compute_parent_directory(char *pwd);

// ft_exit.c

void			ft_exit(t_rline *line, t_env_var **env_list,
					t_process_list **head_process);

// ft_buildtins_env.c

void			ft_env(t_env_var *env, int fd, char *str);
void			ft_unset(t_env_var **env, char *str);
void			ft_export(t_process_list **info_process, t_env_var **env, int fd);

// ft_buildtins_echo.c

void			ft_echo(t_process_list *info_process, int fd);

// ft_process_utility.c

int				is_operator(char *token);
void			checking_redirection(char ***tokens,
					t_process_list	*current_node);
int				is_flag(char *token);
void			handle_argument(t_process_list *current_process,
					char *token, int *arg_index);
t_process_list	*handle_list_creation(t_process_list *current_node,
					char ***tokens, int *arg_index);

// ft_handle_fd.c

int				open_file(char *file, int redirection);
char			*read_file(int fd);

// pipe

void			ft_execute_pipe_line(t_env_var **env, t_process_list *process);

#endif
