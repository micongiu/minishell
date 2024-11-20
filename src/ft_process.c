#include "../minishell.h"
void	ft_add_process_node(t_process_list **process_list, t_process_list *new_var)
{
	t_process_list *temp;

	temp = *process_list;
	if (!process_list)
		return ;
	if (!*process_list)
		*process_list = new_var;
	else
	{
		while (temp->next)
			temp = temp->next;
		temp->next = new_var;
	}
}
t_process_list *ft_create_process_node() {
	t_process_list *node = malloc(sizeof(t_process_list));
	if (!node)
	{
		printf("err_ft_create_process_node\n");
		return (NULL);
	}
	node->command = NULL;
	node->option = NULL;
	node->file_fd = NULL;
	node->redirection = 0;
	node->full_process = NULL;
	node->argument = NULL;
	node->next = NULL;
	return node;
}

//chat gpt, per printare la lista
void print_process_list(t_process_list *head) {
    while (head) {
        printf("Command: %s\n", head->command);
        if (head->option) printf("Option: %s\n", head->option);
        if (head->argument) printf("Argument: %s\n", head->argument);
        if (head->file_fd) {
            printf("File FD: %s\n", head->file_fd);
            printf("Redirection: %d\n", head->redirection);
        }
        printf("----\n");
        head = head->next;
    }
}

t_process_list *ft_init_process_list(char **tokens) {
	t_process_list	*head = NULL;
	t_process_list	*current_node = NULL;
	char			*temp;

	temp = NULL;

	while (*tokens)
	{
		if (!current_node)
			current_node = ft_create_process_node();

		if (ft_strncmp(*tokens, "<", 2) == 0)
		{
			current_node->redirection = 1;
			tokens++;
			current_node->file_fd = ft_strdup_lib(*tokens);
		}
		else if (ft_strncmp(*tokens, ">", 2) == 0)
		{
			current_node->redirection = 2;
			tokens++;
			current_node->file_fd = ft_strdup_lib(*tokens);
		}
		else if (ft_strncmp(*tokens, "<<", 3) == 0)
		{
			current_node->redirection = 3;
			tokens++;
			current_node->file_fd = ft_strdup_lib(*tokens);
		}
		else if (ft_strncmp(*tokens, ">>", 3) == 0)
		{
			current_node->redirection = 4;
			tokens++;
			current_node->file_fd = ft_strdup_lib(*tokens);
		}
		else if (!current_node->command)
			current_node->command = ft_strdup_lib(*tokens);
		else if (**tokens == '-')
			current_node->option = ft_strdup_lib(*tokens);
		else
		{
			if (!current_node->argument)
				current_node->argument = ft_strdup_lib(*tokens);
			else
			{
				char *temp = malloc(sizeof(char) * (ft_strlen_lib(current_node->argument) + ft_strlen_lib(*tokens) + 2 ));
				
				free(current_node->argument);
				current_node->argument = temp;
			}
		}
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

