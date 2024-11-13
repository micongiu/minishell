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
t_process_list ft_create_process_node();

void	ft_init_process_list(char **mat, t_process_list **process_list)
{
	t_var_count2	count;
	char	*command;
	char	*option;
	char	*full_process;

	count.a = 0;
	count.b = 0;
	count.c = 0;
	command = NULL;
	option = NULL;
	full_process = NULL;

	while(mat[count.a] != NULL)
	{
		if((mat[count.a][0] == '|' || mat[count.a][0] == '>' || mat[count.a][0] == '<') && (mat[count.a][1] == '\0' || mat[count.a][1] == '>' || mat[count.a][1] == '<'))
		{
			
			if(count.a == 0)
			{
				printf("ERROR\n");
				break;
			}
			if((count.a - count.b) == 1)
			{
				command = calloc(ft_strlen_lib(mat[(count.a)]) + 1, sizeof(char));
				if(!ft_strlcpy(command, mat[count.a], ft_strlen_lib(mat[(count.a)])+1))
					printf("ERROR 1\n");
				ft_add_process_node(process_list, ft_create_process_node(command, option, full_process));
				printf("%s\n", command);
				free(command);
				command = NULL;
			}
			printf("--------------------\n");
		}
		count.b = count.a;
		count.a++;
	}
}
