#include "../../minishell.h"

int	g_status;

void	ft_signal_handle(int signal)
{
	if (signal == SIGINT)
	{
		g_status = 130;
		rl_replace_line("", 1);
		ft_putendl_fd("", 1);
		if (rl_on_new_line() == -1)
			exit (EXIT_FAILURE);
		rl_redisplay();
	}
}
