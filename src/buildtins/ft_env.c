#include "../../minishell.h"

// print all the env_list

void	ft_env(t_env_var *env, int fd, char *str)
{
	t_env_var	*current;

	if (str)
			ft_error(14, str, 127);
	current = env;
	while (current != NULL)
	{
		ft_putstr_fd(current->name, fd);
		ft_putchar_fd('=', fd);
		ft_putstr_fd(current->value, fd);
		ft_putchar_fd('\n', fd);
		current = current->next;
	}
}
