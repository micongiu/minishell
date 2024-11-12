#include "../minishell.h"

void	ft_init_process_list(char **mat, t_process_list **process_list)
{
	int i;

	i = 0;
	while(mat[i] != NULL)
	{
		if((mat[i][0] == '|' || mat[i][0] == '>' || mat[i][0] == '<') && (mat[i][1] == '\0' || mat[i][1] == '>' || mat[i][1] == '<'))
			printf("--------------------\n");
		i++;
	}
}

int	ft_count_token_modded(char *input)
{
	int i;
	int j;
	
	i = 0;
	j = 0;
	while(input[i] != '\0')
	{
		while(is_space(input[i]))
			i++;
		if(input[i++] == '"' || input[i++] == '\'')
		{
			while(input[i] != '"' && input[i] != '\'')
				i++;
			j++;
			i++;
		}
		if(!is_space(input[i]))
		{
			j++;
			while(!is_space(input[i]) && input[i] != '\0')
				i++;
		}
	}
	return (j);
}
