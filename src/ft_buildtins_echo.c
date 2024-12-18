#include "../minishell.h"

int	ft_echo_utility(char *option)
{
	int	j;

	if (option && option[0] == '-' && option[1])
	{
		j = 1;
		while (option[j] == 'n')
			j++;
		if (option[j] == '\0')
			return (0);
	}
	return (1);
}

void	ft_echo(t_process_list *info_process, int fd)
{
	int		i;
	int		newline;
	char	*tmp;

	i = 1;
	tmp = NULL;
	newline = ft_echo_utility(info_process->option);
	if (newline == 0)
		i++;
	while (info_process->argument[i])
	{
		if (ft_strlen_lib(info_process->argument[i]) > 0)
		{
			tmp = remove_quotes(info_process->argument[i]);
			if (ft_strlen_lib(tmp) > 0)
				ft_putstr_fd(tmp, fd);
			free(tmp);
		}
		if (info_process->argument[i + 1])
			ft_putchar_fd(' ', fd);
		i++;
	}
	if (newline == 1)
		write(fd, "\n", 1);
}
