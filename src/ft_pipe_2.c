#include "../minishell.h"

void	ft_execute_pipe_line(t_env_var **env, t_process_list *process)
{
	char	**env_mat;

	env_mat = ft_list_to_arr(*env);
	if (process->next == NULL && ((ft_strncmp(process->command, "cd", 3) == 0)
			|| (ft_strncmp(process->command, "pwd", 4) == 0)
			|| (ft_strncmp(process->command, "echo", 5) == 0)
			|| (ft_strncmp(process->command, "env", 4) == 0)
			|| (ft_strncmp(process->command, "export", 7) == 0)
			|| (ft_strncmp(process->command, "unset", 6) == 0)
			|| (ft_strncmp(process->command, "exit", 5) == 0)))
		execute_command(process, env, env_mat);
	else
		exec_pipe_loop(env, process, env_mat);
	free_matrix((void **)env_mat);
}

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
	else
		process->fd = 1;
}
