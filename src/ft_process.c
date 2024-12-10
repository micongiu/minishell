#include "../minishell.h"

void	ft_add_process_node(t_process_list **process_list, t_process_list *new_var)
{
	t_process_list *temp;

	temp = *process_list;
	if (!*process_list)
		*process_list = new_var;
	else
	{

		while (temp->next)
			temp = temp->next;
		temp->next = new_var;
	}
}

t_process_list	*ft_create_process_node(char **tokens)
{
	t_process_list *node;
	int i;
	int j;

	i = 0;
	j = 0;
	node = ft_calloc(1, sizeof(t_process_list));
	while((tokens[i]) && (ft_strncmp(tokens[i], ">", 2) != 0) &&
		(ft_strncmp(tokens[i], "<", 2) != 0) &&
		(ft_strncmp(tokens[i], ">>", 3) != 0) &&
		(ft_strncmp(tokens[i], "<<", 3) != 0) &&
		(ft_strncmp(tokens[i], "|", 2) != 0))
		i++;
	node->command = NULL;
	node->option = NULL;
	node->file_fd = NULL;
	node->redirection = 0;
	node->full_process = NULL;
	node->argument = ft_calloc(sizeof(char*), i + 1);
	node->next = NULL;
	return node;
}

void print_process_list(t_process_list *head)
{
	while (head != NULL) { // Itera finché ci sono nodi nella lista
		printf("Command: %s\n", head->command);
		if (head->option) {
			printf("Option: %s\n", head->option);
		}

		int i = 0;
		while (head->argument != NULL && head->argument[i] != NULL)
		{ // Controlla se 'argument' è valido
			printf("Argument: %s\n", head->argument[i]);
			i++;
		}

		if (head->file_fd) {
			printf("File FD: %s\n", head->file_fd); // Usa %d se file_fd è un int
			printf("Redirection: %d\n", head->redirection);
		}

		printf("----\n");
		head = head->next; // Passa al nodo successivo
	}
}

// Helper function to check if a token is an operator
int	is_operator(char *token)
{
	return (ft_strncmp(token, ">", 1) == 0 ||
			ft_strncmp(token, "<", 1) == 0 ||
			ft_strncmp(token, ">>", 2) == 0 ||
			ft_strncmp(token, "<<", 2) == 0 ||
			ft_strncmp(token, "|", 1) == 0);
}

void	checking_redirection(char **tokens, t_process_list	*current_node)
{
	if (ft_strncmp(*tokens, "<", 1) == 0)
	{
		current_node->redirection = 1;
		tokens++;
		current_node->file_fd = ft_strdup_lib(*tokens);
	}
	else if (ft_strncmp(*tokens, ">", 1) == 0)
	{
		current_node->redirection = 2;
		tokens++;
		current_node->file_fd = ft_strdup_lib(*tokens);
	}
	else if (ft_strncmp(*tokens, "<<", 2) == 0)
	{
		current_node->redirection = 3;
		tokens++;
		current_node->file_fd = ft_strdup_lib(*tokens);
	}
	else if (ft_strncmp(*tokens, ">>", 2) == 0)
	{
		current_node->redirection = 4;
		tokens++;
		current_node->file_fd = ft_strdup_lib(*tokens);
	}
}

// Helper function to check if a token is an option/flag
int	is_flag(char *token) {
	return (token && *token == '-');
}

// Helper function to handle arguments and options for the current process
void	handle_argument(t_process_list *current_process, char *token, int *arg_index)
{
	if (!current_process->command) 
		current_process->command = ft_strdup_lib(token);
	if (is_flag(token))
		current_process->option = ft_strdup_lib(token);
	current_process->argument[*arg_index] = ft_strdup_lib(token);
	(*arg_index)++;
}

t_process_list	*ft_init_process_list(char **tokens)
{
	t_process_list	*head;
	t_process_list	*current_node;
	char			*temp;
	int				arg;

	arg = 0;
	temp = NULL;
	head = NULL;
	current_node = NULL;
	while (*tokens)
	{
		if (!current_node)
		{
			current_node = ft_create_process_node(tokens);
			arg = 0;
		}
		else if (!current_node->command)
		{
			current_node->argument[arg] = ft_strdup_lib(*tokens);
			current_node->command = ft_strdup_lib(*tokens);
			arg++;
		}
		else if (!is_operator(*tokens))
			handle_argument(current_node, *tokens, &arg);
		else if((ft_strncmp(*(tokens), "|", 1) != 0) && !*(tokens) && !(**tokens == '-'))
		{
			current_node->argument[arg] = ft_strdup_lib(*tokens);
			arg++;
		}
		checking_redirection(tokens, current_node);
		if (!*(tokens + 1) || ft_strncmp(*(tokens + 1), "|", 2) == 0)
		{
			ft_add_process_node(&head, current_node);
			current_node = NULL;
			if (*(tokens + 1))
				tokens++;
		}
		tokens++;
	}
	print_process_list(head);
	return head;
}

void free_process_list(t_process_list **cur)
{
	t_process_list *tmp;
	int				j;

	j = 0;
	while (*cur != NULL)
	{
		j = 0;
		tmp = (*cur)->next;
		free((*cur)->command);
		if ((*cur)->option)
			free((*cur)->option);
		if ((*cur)->file_fd)
			free((*cur)->file_fd);
		if ((*cur)->full_process)
			free((*cur)->full_process);
		if ((*cur)->argument)
		{
			while ((*cur)->argument[j] != NULL)
				free((*cur)->argument[j++]);
			free((*cur)->argument);
		}
		free(*cur);
		*cur = tmp;
	}
}

// gestire gli errori se si danno molteplici redirection 

//serve commentare e mettere a norma


