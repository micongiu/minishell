#include "../../minishell.h"

void	exec_child_process(t_process_list *process, t_env_var **env,
							char **env_mat, int prev_fd, int *pipe_fd)
{
	if (prev_fd != -1)
	{
		if (dup2(prev_fd, STDIN_FILENO) < 0)
			error_and_free("Error duplicating STDIN", env_mat, 1);
		close(prev_fd);
	}
	if (process->next)
	{
		if (dup2(pipe_fd[1], STDOUT_FILENO) < 0)
			error_and_free("Error duplicating STDOUT", env_mat, 1);
	}
	if (pipe_fd[0] != -1)
		close(pipe_fd[0]);
	if (pipe_fd[1] != -1)
		close(pipe_fd[1]);
	handle_redirection(process);
	if (is_builtins(process->command))
	{
		execute_command(process, env, env_mat);
		exit(EXIT_SUCCESS);
	}
	else
		execute_not_b(process, env_mat);
}

void	execute_command(t_process_list *process, t_env_var **env_list,
		char **env_mat)
{
	if (ft_strncmp (process->command, "cd", 3) == 0)
		ft_cd(process, env_list);
	else if (ft_strncmp (process->command, "pwd", 4) == 0)
		ft_pwd(env_list);
	else if (ft_strncmp (process->command, "echo", 5) == 0)
		ft_echo(process);
	else if (ft_strncmp (process->command, "env", 4) == 0)
		ft_env(*env_list, process->argument[1]);
	else if (ft_strncmp (process->command, "export", 7) == 0)
		ft_export(&process, env_list);
	else if (ft_strncmp (process->command, "unset", 6) == 0
		&& !(process->option))
		ft_unset(env_list, process->argument[1]);
	else if (ft_strncmp(process->command, "exit", 5) == 0)
		ft_exit(NULL, &*env_list, &process, env_mat);
}
void	execute_not_b(t_process_list *process,
		char **env_mat)
{
	execve(ft_strjoin_lib("/bin/", process->argument[0]),
		process->argument, env_mat);
	perror("Error executing command with execve");
	exit(EXIT_FAILURE);
}

void	exec_pipe_loop(t_env_var **env, t_process_list *process, char **env_mat,
		int *pipe_fd)
{
	int		prev_fd;
	pid_t	pid;

	prev_fd = -1;
	while (process)
	{
		if (process->next && pipe(pipe_fd) == -1)
			error_and_free("Error creating pipe", env_mat, 1);
		pid = fork();
		if (pid == -1)
			error_and_free("Error during fork", env_mat, 1);
		if (pid == 0)
			exec_child_process(process, env, env_mat, prev_fd, pipe_fd);
		else
		{
			if (prev_fd != -1)
				close(prev_fd);
			if (pipe_fd[1] != -1)
				close(pipe_fd[1]);
			prev_fd = pipe_fd[0];
		}
		process = process->next;
	}
	while (wait(NULL) > 0)
		;
}

void	ft_execute_pipe_line(t_env_var **env, t_process_list *process)
{
	char	**env_mat;
	int		pipe_fd[2];

	pipe_fd[0] = -1;
	pipe_fd[1] = -1;
	env_mat = ft_list_to_arr(*env);
	if (process->next == NULL && is_builtins(process->command) != 0)
		{
			handle_redirection(process);
			execute_command(process, env, env_mat);
			if (dup2(process->in_file, STDIN_FILENO) < 0)
				error_and_free("Error duplicating output file descriptor", env_mat, 1);
			if (dup2(process->out_file, STDOUT_FILENO) < 0)
				error_and_free("Error duplicating output file descriptor", env_mat, 1);
			process->in_file = 0;
			process->out_file = 1;
		}
	else
		exec_pipe_loop(env, process, env_mat, pipe_fd);
	free_matrix((void **)env_mat);
}
