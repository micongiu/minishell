/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmedyns <anmedyns@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 16:10:56 by anmedyns          #+#    #+#             */
/*   Updated: 2024/12/27 16:10:59 by anmedyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

	i = 0;
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
	node->child = 0;
	node->heredoc = 0;
	return (node);
}

t_process_list	*ft_init_process_list(char **tokens)
{
	t_process_list	*head;
	t_process_list	*current_node;
	int				arg;
	char			**tmp;

	arg = 0;
	head = NULL;
	tmp = tokens;
	current_node = NULL;
	while (*tmp)
	{
		current_node = handle_list_creation(current_node, &tmp, &arg);
		if (!*(tmp + 1) || ft_strncmp(*(tmp + 1), "|", 2) == 0)
		{
			ft_add_process_node(&head, current_node);
			current_node = NULL;
			if (*(tmp + 1))
				tmp++;
		}
		tmp++;
	}
	free_matrix((void **)tokens);
	return (head);
}

void	free_process_list(t_process_list **cur)
{
	t_process_list	*tmp;
	int				j;

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
