#include "../minishell.h"

void	ft_echo(t_process_list *info_process, int fd)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	if (info_process->option)
	{
		if (ft_strncmp(info_process->option, "-n", 2) == 0)
		{
			flag = 1;
			i++;
		}
	}
	while (info_process->argument[i])
	{
		ft_putstr_fd(info_process->argument[i], fd);
		if (info_process->argument[i + 1])
			ft_putchar_fd(' ', fd);
		i++;
	}
	if (flag == 1)
		write(fd, "\n", 1);
}
