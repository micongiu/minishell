#include "../../minishell.h"

// print all the env_list

void	ft_env(t_env_var *env, char *str)
{
	t_env_var	*current;

	if (str)
		error_and_free("minishell: Not a directory: ", NULL, 1);
	current = env;
	while (current != NULL)
	{
		ft_putstr_fd(current->name, STDOUT_FILENO);
		ft_putchar_fd('=', STDOUT_FILENO);
		ft_putstr_fd(current->value, STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		current = current->next;
	}
}
