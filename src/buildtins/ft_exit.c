#include "../../minishell.h"

void	ft_exit(t_rline *line, t_env_var **env_list,
	t_process_list **head_process)
{
	if (line->input)
	{
		free(line->input);
		free(line);
	}
	if (env_list)
		free_env_list(env_list);
	if (head_process)
		free_process_list(head_process);
	clear_history();
	printf("exit\n");
	exit(0);
}
