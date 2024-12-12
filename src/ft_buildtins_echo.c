#include "../minishell.h"

void	ft_echo(t_process_list *info_process, int fd)
{
	int	i;

	i = 0;
	while (info_process->argument[i])
	{
		ft_putstr_fd(info_process->argument[i], fd);
		if (info_process->argument[i + 1])
			ft_putchar_fd(' ', fd);
		i++;
	}
	if (info_process->option)
		if (ft_strncmp(info_process->option, "-n", 2) == 0)
			write(fd, "\n", 1);
}
