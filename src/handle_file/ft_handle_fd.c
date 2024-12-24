#include "../../minishell.h"

extern int	g_status;

// int	open_file(char *file, int redirection)
// {
// 	int	fd;

// 	fd = 0;
// 	// if (access(file, F_OK) == -1)
// 	// 	error("minishell: No such file or directory");
// 	// if (redirection == 1 && access(file, R_OK) == -1)
// 	// 	error("minishell: permission denied");
// 	// if ((redirection == 2 || redirection == 4) && access(file, W_OK) == -1)
// 	// 	error("minishell: permission denied");
// 	if (redirection == S_IN_RED)
// 		fd = open(file, O_RDONLY);
// 	else if (redirection == S_OUT_RED)
// 		fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0666);
// 	else if (redirection == D_OUT_RED)
// 		fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0666);
// 	return (fd);
// }

void	handle_input_redirection(t_process_list *process)
{
	int	fd;

	fd = open(process->file_fd, O_RDONLY);
	if (fd < 0)
		error_and_free("Error opening input file", NULL);
	if (dup2(fd, STDIN_FILENO) < 0)
		error_and_free("Error duplicating input file descriptor", NULL);
	close(fd);
}

void	handle_output_redirection(t_process_list *process)
{
	int	fd;

	fd = open(process->file_fd, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		error_and_free("Error opening output file", NULL);
	if (dup2(fd, STDOUT_FILENO) < 0)
		error_and_free("Error duplicating output file descriptor", NULL);
	close(fd);
}

void	handle_append_redirection(t_process_list *process)
{
	int	fd;

	fd = open(process->file_fd, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		error_and_free("Error opening output file in append mode", NULL);
	if (dup2(fd, STDOUT_FILENO) < 0)
		error_and_free("Error duplicating output file descriptor", NULL);
	close(fd);
}

void	handle_redirection(t_process_list *process)
{
	if (process->redirection == 1 && process->file_fd)
		handle_input_redirection(process);
	else if (process->redirection == 2 && process->file_fd)
		handle_output_redirection(process);
	else if (process->redirection == 3 && process->file_fd)
		handle_append_redirection(process);
}
