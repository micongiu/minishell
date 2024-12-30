/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmedyns <anmedyns@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 15:59:22 by micongiu          #+#    #+#             */
/*   Updated: 2024/12/30 17:08:38 by anmedyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

extern int		g_status;

// Structures
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
	int						redirection;
	char					*full_process;
	char					**argument;
	int						in_file;
	int						out_file;
	struct s_process_list	*next;
}	t_process_list;

typedef struct s_rline
{
	char	*input;
	char	**mat_input;
}	t_rline;

typedef struct s_var_count
{
	int			i;
	int			j;
	int			k;
}	t_var_count;

// Enums

enum e_redirection
{
	S_IN_RED = 1,
	S_OUT_RED = 2,
	D_OUT_RED = 3,
	HERDOC = 4
};

// main.c
char			*remove_quotes(char *str);
int				main(int argc, char **argv, char **env);
t_var_count		ft_ex_dollar(char *line, char *token, t_env_var *env,
					t_var_count count);

// Builtins

// ft_cd.c
void			ft_cd(t_process_list *process, t_env_var **env_list);

// ft_echo.c
void			ft_echo(t_process_list *info_process);

// Builtins

// ft_env.c
void			ft_env(t_env_var *env, char *str);

// ft_unset.c
void			ft_unset(t_env_var **env, char *str);

// ft_export.c
void			ft_export(t_process_list **info_process, t_env_var **env);

// ft_exit.c
void			ft_exit(char *line, t_env_var **env_list,
					t_process_list **head_process, char **env_mat);

// ft_pwd.c
void			ft_pwd(t_env_var **env_list);

// Environment

// ft_env_list.c
t_env_var		*get_node_of(t_env_var **env_list, char *key);
void			ft_add_env_var(t_env_var **env_list, char *name, char *value);
void			ft_init_env_list(t_env_var **env_list, char **env);
void			free_env_list(t_env_var **cur);

// Execute

// ft_pipe.c
void			ft_execute_pipe_line(t_env_var **env, t_process_list *process);
void			execute_not_b(t_process_list *process, char **env_mat);
void			execute_command(t_process_list *process, t_env_var **env_list,
					char **env_mat);

// Handle File

// ft_heredoc.c

char			*ft_heredoc(char *keyword);

// ft_handle_fd.c
void			handle_input_redirection(t_process_list *process);
void			handle_output_redirection(t_process_list *process);
void			handle_append_redirection(t_process_list *process);
void			handle_redirection(t_process_list *process);

// Parser

// ft_process.c
void			free_process_list(t_process_list **cur);
t_process_list	*ft_create_process_node(char **tokens);
t_process_list	*ft_init_process_list(char **mat);

// ft_process_utility.c
int				is_operator(char *token);
void			checking_redirection(char ***tokens,
					t_process_list *current_node);
int				is_flag(char *token);
void			handle_argument(t_process_list *current_process,
					char *token, int *arg_index);
t_process_list	*handle_list_creation(t_process_list *current_node,
					char ***tokens, int *arg_index);

// Signal Handling

// ft_signal_handle.c
void			ft_signal_handle(int signal);
void			ft_signal_heredoc(int signal);

// Tokenizer

// ft_tokenizer.c
char			**ft_tokenizer(char *input, t_env_var *env);

// ft_tokenizer_utility.c
int				is_space(char c);
int				ft_check_quote(char *input);

// ft_tokenizer_counter.c
int				ft_count(char *input, int i, t_env_var *env);
int				ft_count_token(char *input);

int				process_special_tokens(char *input, int *i, int *count_i);
int				handle_special_characters(char *input, int *i);
t_var_count		handlett_special_tokens(char *token, char *line,
					t_var_count count);
int				is_special_token_after_quotes(char *line, int i);

// Utilities

// ft_utility.c
void			error_and_free(char *str, char **env, int status);
void			free_matrix(void **matrix);
int				ft_count_node(t_env_var *env);
char			**ft_list_to_arr(t_env_var *env_h);
int				is_builtins(char *str);

// ft_utility_2.c
void			close_and_update_fd(int *prev_fd, int *pipe_fd);

#endif
