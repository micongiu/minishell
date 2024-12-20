#include "../../minishell.h"

void	ft_exit(t_rline *line, t_env_var **env_list,
	t_process_list **head_process)
{
	free(line->input);
	free(line);
	free_env_list(env_list);
	free_process_list(head_process);
	clear_history();
	printf("exit\n");
}