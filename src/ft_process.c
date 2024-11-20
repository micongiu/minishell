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
	node->argument1 = NULL;
	node->argument2 = NULL;
	node->argument3 = NULL;
	node->next = NULL;
	return node;
}

//chat gpt, per printare la lista
void print_process_list(t_process_list *head) {
    while (head) {
        printf("Command: %s\n", head->command);
        if (head->option) printf("Option: %s\n", head->option);
        if (head->argument1) printf("Argument1: %s\n", head->argument1);
 		if (head->argument2) printf("Argument2: %s\n", head->argument2);
		if (head->argument3) printf("Argument3: %s\n", head->argument3);
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
			current_node = ft_create_process_node();//se non esiste un nodo , lo crea

		if (ft_strncmp(*tokens, "<", 2) == 0) //da qui
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
		else if (ft_strncmp(*tokens, "<<", 3) == 0) // ci salviamo il delemitatore subito dopo le <<
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
		}										//a qui controlla eventuali redirection e si salva il file in cui dovra essere scritto l'output o viceversa
		else if (!current_node->command)
			current_node->command = ft_strdup_lib(*tokens);
		else if (**tokens == '-')
			current_node->option = ft_strdup_lib(*tokens);
		else
		{
			if (!current_node->argument1)
				current_node->argument1 = ft_strdup_lib(*tokens);
			else if (!current_node->argument2)
				current_node->argument2 = ft_strdup_lib(*tokens);
			else if (!current_node->argument3)
				current_node->argument3 = ft_strdup_lib(*tokens);
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

void free_process_list(t_process_list **cur)
{
	t_process_list *tmp;

	tmp = NULL;
	while (*cur != NULL)
	{
		tmp = (*cur)->next;
		free((*cur)->command);
		free((*cur)->option);
		free((*cur)->file_fd);
		free((*cur)->full_process);
		free((*cur)->argument1);
		free((*cur)->argument2);
		free((*cur)->argument3);
		free(*cur);
		*cur = tmp;
	}
}

//Il simbolo > è utilizzato per redirigere l'output di un comando verso un file. Se il file non esiste, viene creato; se il file esiste già, il suo contenuto viene sovrascritto.
//Il simbolo < è utilizzato per redirigere l'input da un file invece che dalla tastiera. Quando un comando si aspetta dell'input da tastiera, < permette di leggere i dati da un file invece che dall'utente.
//Il simbolo << è utilizzato per creare un "here document", che permette di passare un blocco di testo direttamente a un comando. Questo è utile quando vuoi fornire più righe di input a un comando senza dover scrivere un file separato.
//Il simbolo >> è simile a >, ma invece di sovrascrivere il contenuto del file, aggiunge (append) l'output alla fine del file esistente. Se il file non esiste, viene creato.




//serve commentare e mettere a norma
//si memorizza i primi 3  argomenti se ci dovessero essere e gli altri li skippa
//aggiungere eventuale ERROR per troppi argomenti passati
