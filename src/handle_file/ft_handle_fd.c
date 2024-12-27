#include "../../minishell.h"

extern int	g_status;

void	handle_input_redirection(t_process_list *process)
{
	int	fd;

	fd = open(process->file_fd, O_RDONLY);
	if (fd < 0)
		error_and_free("Error opening input file", NULL, 1);
	if (dup2(fd, STDIN_FILENO) < 0)
		error_and_free("Error duplicating input file descriptor", NULL, 1);
	close(fd);
}

void	handle_output_redirection(t_process_list *process)
{
	int	fd;

	fd = open(process->file_fd, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		error_and_free("Error opening output file", NULL, 1);
	if (dup2(fd, STDOUT_FILENO) < 0)
		error_and_free("Error duplicating output file descriptor", NULL, 1);
	close(fd);
}

void	handle_append_redirection(t_process_list *process)
{
	int	fd;

	fd = open(process->file_fd, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		error_and_free("Error opening output file in append mode", NULL, 1);
	if (dup2(fd, STDOUT_FILENO) < 0)
		error_and_free("Error duplicating output file descriptor", NULL, 1);
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
	else if (process->redirection == 4 && process->file_fd)
	{
		handle_input_redirection(process);
		unlink(process->file_fd);
	}
}
