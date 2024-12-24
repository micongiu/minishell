#include "../../minishell.h"

void	ft_exit(char *line, t_env_var **env_list,
	t_process_list **head_process, char **env_mat)
{
	if (line)
		free(line);
	if (env_list)
		free_env_list(env_list);
	if (head_process)
		free_process_list(head_process);
	if(env_mat)
		free_matrix((void *)env_mat);
	printf("exit\n");
	exit(0);
}
