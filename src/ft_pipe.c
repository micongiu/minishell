#include "../minishell.h"

static void	handle_input_redirect(int prev_fd, int *pipe_fd,
		t_process_list *process, char **env_mat)
{
	if (prev_fd != -1)
	{
		if (dup2(prev_fd, STDIN_FILENO) < 0)
			error_and_free("Error duplicating STDIN", env_mat);
		close(prev_fd);
	}
	if (process->next)
	{
		if (dup2(pipe_fd[1], STDOUT_FILENO) < 0)
			error_and_free("Error duplicating STDOUT", env_mat);
	}
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	handle_redirection(process);
}

static void	execute_builtin_or_external(t_process_list *process,
	t_env_var **env, char **env_mat)
{
	if (is_builtins(process->command))
	{
		execute_command(process, env, env_mat);
		exit(EXIT_SUCCESS);
	}
	else
	{
		execute_not_b(process, env_mat);
	}
}

void	exec_child_process(t_process_list *process, t_env_var **env,
							char **env_mat, int prev_fd, int *pipe_fd)
{
	handle_input_redirect(prev_fd, pipe_fd, process, env_mat);
	execute_builtin_or_external(process, env, env_mat);
}

void	exec_parent_process(int *prev_fd, int *pipe_fd)
{
	if (*prev_fd != -1)
		close(*prev_fd);
	if (pipe_fd[1] != -1)
		close(pipe_fd[1]);
	*prev_fd = pipe_fd[0];
}

void	exec_pipe_loop(t_env_var **env, t_process_list *process, char **env_mat)
{
	int		pipe_fd[2];
	int		prev_fd;
	pid_t	pid;

	pipe_fd[0] = -1;
	pipe_fd[1] = -1;
	prev_fd = -1;
	while (process)
	{
		if (process->next && pipe(pipe_fd) == -1)
			error_and_free("Error creating pipe", env_mat);
		pid = fork();
		if (pid == -1)
			error_and_free("Error during fork", env_mat);
		if (pid == 0)
			exec_child_process(process, env, env_mat, prev_fd, pipe_fd);
		else
		{
			exec_parent_process(&prev_fd, pipe_fd);
		}
		process = process->next;
	}
	while (wait(NULL) > 0)
		;
}
