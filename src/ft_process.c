#include "../minishell.h"

void	ft_add_process_node(t_process_list **process_list,
			t_process_list *new_var)
{
	t_process_list	*temp;

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
	t_process_list	*node;
	int				i;
	int				j;

	i = 0;
	j = 0;
	node = ft_calloc(1, sizeof(t_process_list));
	while ((tokens[i]) && (ft_strncmp(tokens[i], "|", 2) != 0))
		i++;
	node->command = NULL;
	node->option = NULL;
	node->file_fd = NULL;
	node->redirection = 0;
	node->full_process = NULL;
	node->argument = ft_calloc(sizeof(char *), i + 2);
	node->next = NULL;
	return (node);
}

void print_process_list(t_process_list *head)
{
	while (head != NULL) {
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
			print("Fd file: %d\n", head->fd);
			printf("Redirection: %d\n", head->redirection);
		}

		printf("----\n");
		head = head->next; // Passa al nodo successivo
	}
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
		current_node = handle_list_creation(current_node, &tokens, &arg);
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
	return (head);
}

void	free_process_list(t_process_list **cur)
{
	t_process_list	*tmp;
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
		if ((*cur)->fd)
			close((*cur)->file_fd);
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
