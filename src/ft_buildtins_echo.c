#include "../minishell.h"

// void	ft_echo(t_process_list *info_process, int fd)
// {
// 	int	i;
// 	int	newline;

// 	i = 1;
// 	newline = 1;
// 	if (info_process->option)
// 	{
// 		if (ft_strncmp(info_process->option, "-n", 3) == 0)
// 		{
// 			newline = 0;
// 			i++;
// 		}
// 	}
// 	while (info_process->argument[i])
// 	{
// 		ft_putstr_fd(info_process->argument[i], fd);
// 		if (info_process->argument[i + 1])
// 			ft_putchar_fd(' ', fd);
// 		i++;
// 	}
// 	if (newline == 1)
// 		write(fd, "\n", 1);
// }

void	ft_echo(t_process_list *info_process, int fd)
{
	int	i;
	int	j;
	int	newline;

	i = 1;
	newline = 1;
	if (info_process->option && info_process->option[0] == '-')
	{
		j = 1;
		while (info_process->option[j] == 'n')
			j++;
		if (info_process->option[j] == '\0')
		{
			newline = 0;
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
	if (newline == 1)
		write(fd, "\n", 1);
}
