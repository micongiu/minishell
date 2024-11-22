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

t_process_list	*ft_create_process_node(char **tokens)
{
	t_process_list *node;
	int i;
	int j;

	i = 0;
	j = 0;
	node = ft_calloc(1, sizeof(t_process_list));

	while((tokens[i] != NULL) && (ft_strncmp(tokens[i], ">", 2) != 0) && (ft_strncmp(tokens[i], "<", 2) != 0) && (ft_strncmp(tokens[i], ">>", 3) != 0) && (ft_strncmp(tokens[i], "<<", 3) != 0) && (ft_strncmp(tokens[i], "|", 2) != 0))
			{
				i++;
				printf("valore TOKENS %i = %s\n", i, tokens[i]);
			}
	node->command = NULL;
	node->option = NULL;
	node->file_fd = NULL;
	node->redirection = 0;
	node->full_process = NULL;
	node->argument = malloc(sizeof(char*) * i);

	while(j < i)
	{
		node->argument[j] = NULL;
		j++;
	}
	node->next = NULL;
	return node;
}

//chat gpt, per printare la lista

void print_process_list(t_process_list *head) {
	int i;
    while (head) {
		i = 0;
        printf("Command: %s\n", head->command);
        if (head->option) printf("Option: %s\n", head->option);
        if (head->argument[i])
		{
			while(head->argument[i])
				printf("Argument: %s\n", head->argument[i]);
				i++;
		}
        if (head->file_fd) {
            printf("File FD: %s\n", head->file_fd);
            printf("Redirection: %d\n", head->redirection);
        }
        printf("----\n");
        head = head->next;
    }
}

t_process_list	*ft_init_process_list(char **tokens)
{
	t_process_list	*head = NULL;
	t_process_list	*current_node = NULL;
	char			*temp;
	int arg;

	arg = 0;
	temp = NULL;
	while (*tokens)
	{
		if (!current_node)
		{
			current_node = ft_create_process_node(tokens);//se non esiste un nodo , lo crea
		}
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
		{
			current_node->command = ft_strdup_lib(*tokens);
		}
		else if (**tokens == '-')
		{
			current_node->option = ft_strdup_lib(*tokens);
			current_node->argument[arg] == ft_strdup_lib(*tokens);
			arg++;
		}
		else if((ft_strncmp(*(tokens), "|", 2) != 0) && !*(tokens) && !(**tokens == '-'))
		{
			current_node->argument[arg] == ft_strdup_lib(*tokens);
			arg++;
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

void	free_process_list(t_process_list **cur)
{
	t_process_list	*tmp;
	int i;

	i = 0;
	tmp = NULL;
	while (*cur != NULL)
	{
		tmp = (*cur)->next;
		free((*cur)->command);
		free((*cur)->option);
		free((*cur)->file_fd);
		free((*cur)->full_process);
		while((*cur)->argument[i] != NULL)
		{
			free((*cur)->argument[i]);
			i++;
		}
		free((*cur)->argument);
		free(*cur);
		*cur = tmp;
	}
}

//Il simbolo > è utilizzato per redirigere l'output di un comando verso un file. Se il file non esiste, viene creato; se il file esiste già, il suo contenuto viene sovrascritto.
//Il simbolo < è utilizzato per redirigere l'input da un file invece che dalla tastiera. Quando un comando si aspetta dell'input da tastiera, < permette di leggere i dati da un file invece che dall'utente.
//Il simbolo << è utilizzato per creare un "here document", che permette di passare un blocco di testo direttamente a un comando. Questo è utile quando vuoi fornire più righe di input a un comando senza dover scrivere un file separato.
//Il simbolo >> è simile a >, ma invece di sovrascrivere il contenuto del file, aggiunge (append) l'output alla fine del file esistente. Se il file non esiste, viene creato.


//serve commentare e mettere a norma
//aggiungere eventuale ERROR per troppi argomenti passati



//COSE DA FARE
//salva il full_path come array di stringhe    char[] = {"ciao","duce","ok",NULL};

