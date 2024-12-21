#include "../minishell.h"

int	ft_count_node(t_env_var *env)
{
	int	i;

	i = 0;
	while(env)
	{
		i++;
		env = env->next;
	}
	return(i);
}

char	**ft_list_to_arr(t_env_var *env_h)
{
	char		**env_mat;
	int			i;
	char		*tmp;
	t_env_var	*current;

	current = env_h;
	i = 0;
	env_mat = ft_calloc((ft_count_node(current) + 1), sizeof(char *));
	while (current != NULL)
	{
		tmp = ft_strjoin_lib(current->name, "=");
		env_mat[i] = ft_strjoin_lib(tmp, current->value);
		free(tmp);
		i++;
		current = current->next;
	}
	return(env_mat);
}

int	is_builtins(char *str)
{
	return ((ft_strncmp(str, "cd", 3) == 0)
			|| (ft_strncmp(str, "pwd", 4) == 0)
			|| (ft_strncmp(str, "echo", 5) == 0)
			|| (ft_strncmp(str, "env", 4) == 0)
			|| (ft_strncmp(str, "export", 7) == 0)
			|| (ft_strncmp(str, "unset", 6) == 0)
			|| (ft_strncmp(str, "exit", 5) == 0));
}

void	error_and_free(char *str, char	**env_mat)
{
	perror(str);
	if (env_mat)
		free_matrix((void **)env_mat);
	exit(EXIT_FAILURE);
}
void handle_redirection(t_process_list *process)
{
	if (process->redirection == 1 && process->file_fd) // Input redirection
	{
		int fd = open(process->file_fd, O_RDONLY);
		if (fd < 0)
			error_and_free("Error opening input file", NULL);
		if (dup2(fd, STDIN_FILENO) < 0)
			error_and_free("Error duplicating input file descriptor", NULL);
		close(fd);
	}
	else if (process->redirection == 2 && process->file_fd) // Output redirection
	{
		int fd = open(process->file_fd, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
			error_and_free("Error opening output file", NULL);
		if (dup2(fd, STDOUT_FILENO) < 0)
			error_and_free("Error duplicating output file descriptor", NULL);
		close(fd);
	}
	else if (process->redirection == 3 && process->file_fd) // Append redirection
	{
		int fd = open(process->file_fd, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd < 0)
			error_and_free("Error opening output file in append mode", NULL);
		if (dup2(fd, STDOUT_FILENO) < 0)
			error_and_free("Error duplicating output file descriptor", NULL);
		close(fd);
	}
}
// Child process management
void exec_child_process(t_process_list *process, t_env_var **env,
						char **env_mat, int prev_fd, int *pipe_fd)
{
	if (prev_fd != -1) {
		if (dup2(prev_fd, STDIN_FILENO) == -1)
			error_and_free("Error duplicating STDIN", env_mat);
		close(prev_fd);
	}
	if (process->next) {
		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
			error_and_free("Error duplicating STDOUT", env_mat);
		close(pipe_fd[1]);
	}
	if (pipe_fd[0] != -1)
		close(pipe_fd[0]);
	handle_redirection(process);
	execute_command(process, env, env_mat);
}

// Parent process management
void exec_parent_process(int *prev_fd, int *pipe_fd)
{
	if (*prev_fd != -1)
		close(*prev_fd);
	if (pipe_fd[1] != -1)
		close(pipe_fd[1]);
	*prev_fd = (pipe_fd[0] != -1) ? pipe_fd[0] : -1;
}

// Pipe loop
void exec_pipe_loop(t_env_var **env, t_process_list *process, char **env_mat)
{
	int pipe_fd[2]= {-1, -1};
	int prev_fd = -1;
	pid_t pid;

	while (process) {
		if (process->next && pipe(pipe_fd) == -1)
			error_and_free("Error creating pipe", env_mat);
		pid = fork();
		if (pid == -1)
			error_and_free("Error during fork", env_mat);
		if (pid == 0)
			exec_child_process(process, env, env_mat, prev_fd, pipe_fd);
		else
			exec_parent_process(&prev_fd, pipe_fd);
		process = process->next;
	}
	while (wait(NULL) > 0)
		;
}

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
