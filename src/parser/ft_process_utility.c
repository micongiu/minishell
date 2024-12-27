#include "../../minishell.h"

// Helper function to check if a token is an operator
int	is_operator(char *token)
{
	return (ft_strncmp(token, ">", 2) == 0
		|| ft_strncmp(token, "<", 2) == 0
		|| ft_strncmp(token, ">>", 3) == 0
		|| ft_strncmp(token, "<<", 3) == 0);
}

void	checking_redirection(char ***tokens, t_process_list	*current_node)
{
	if (ft_strncmp(**tokens, "<", 2) == 0)
		current_node->redirection = S_IN_RED;
	else if (ft_strncmp(**tokens, "<<", 3) == 0)
		current_node->redirection = HERDOC;
	else if (ft_strncmp(**tokens, ">", 2) == 0)
		current_node->redirection = S_OUT_RED;
	else if (ft_strncmp(**tokens, ">>", 3) == 0)
		current_node->redirection = D_OUT_RED;
	if (current_node->redirection == HERDOC)
	{
		(*tokens)++;
		current_node->file_fd = ft_strdup(ft_heredoc(**tokens));
	}
	else if (current_node->redirection)
	{
		(*tokens)++;
		current_node->file_fd = ft_strdup_lib(**tokens);
	}
}

// Helper function to check if a token is an option/flag
int	is_flag(char *token)
{
	return (token && *token == '-');
}

// Helper function to handle options for the current process
void	handle_argument(t_process_list *current_process,
	char *token, int *arg_index)
{
	if (is_flag(token))
		current_process->option = ft_strdup_lib(token);
	current_process->argument[*arg_index] = ft_strdup_lib(token);
	(*arg_index)++;
}

t_process_list	*handle_list_creation(t_process_list *current_node,
	char ***tokens, int *arg_index)
{
	if (!current_node)
	{
		current_node = ft_create_process_node((*tokens));
		(*arg_index) = 0;
	}
	if (is_operator(**tokens))
		checking_redirection(tokens, current_node);
	else if (!current_node->command)
	{
		current_node->argument[*arg_index] = ft_strdup_lib(**tokens);
		current_node->command = ft_strdup_lib(**tokens);
		(*arg_index)++;
	}
	else if (*tokens && **(tokens) && (!is_operator(**(tokens)))
		&& (ft_strncmp(**tokens, "|", 2) != 0))
		handle_argument(current_node, **tokens, arg_index);
	else if ((ft_strncmp(**(tokens), "|", 2) != 0) && !**(tokens)
		&& !(***tokens == '-'))
	{
		current_node->argument[*arg_index] = ft_strdup_lib(**tokens);
		(*arg_index)++;
	}
	current_node->in_file = dup(STDIN_FILENO);
	current_node->out_file = dup(STDOUT_FILENO);
	return (current_node);
}
