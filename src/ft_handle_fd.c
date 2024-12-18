#include "../minishell.h"

int	open_file(char *file, int redirection)
{
	int	fd;

	fd = 0;
	// if (access(file, F_OK) == -1)
	// 	error("minishell: No such file or directory");
	// if (redirection == 1 && access(file, R_OK) == -1)
	// 	error("minishell: permission denied");
	// if ((redirection == 2 || redirection == 4) && access(file, W_OK) == -1)
	// 	error("minishell: permission denied");
	if (redirection == 1)
		fd = open(file, O_RDONLY);
	else if (redirection == 2)
		fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	else if (redirection == 4)
		fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0666);
	printf("\n%d\n\n", fd);
	return (fd);
}

char	*read_file(int fd)
{
	char	*tmp;
	char	*str;

	str = NULL;
	tmp = NULL;
	while (1)
	{
		tmp = get_next_line(fd);
		if (tmp == NULL)
			break ;
		ft_strjoin_lib(str, tmp);
		free(tmp);
	}
	return (str);
}
