/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmedyns <anmedyns@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 16:49:23 by anmedyns          #+#    #+#             */
/*   Updated: 2025/01/03 15:35:58 by anmedyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	g_status;

void	exec_child_process(t_process_list *process, t_env_var **env,
							int prev_fd, int *pipe_fd)
{
	char	**env_mat;

	process->child = 1;
	env_mat = ft_list_to_arr(*env);
	if (prev_fd != -1)
	{
		if (dup2(prev_fd, STDIN_FILENO) < 0)
			error_and_free("Error duplicating", env_mat, 1, process->child);
		close(prev_fd);
	}
	if (process->next)
		if (dup2(pipe_fd[1], STDOUT_FILENO) < 0)
			error_and_free("Error duplicating", env_mat, 1, process->child);
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
		ft_env(*env_list, process->argument[1], process->child);
	else if (ft_strncmp (process->command, "export", 7) == 0)
		ft_export(&process, env_list);
	else if (ft_strncmp (process->command, "unset", 6) == 0
		&& !(process->option))
		ft_unset(env_list, process->argument[1], process->child);
	else if (ft_strncmp(process->command, "exit", 5) == 0)
		ft_exit(NULL, &*env_list, &process, env_mat);
}

void	execute_not_b(t_process_list *process,
			char **env_mat)
{
	char	*tmp;

	tmp = NULL;
	if (ft_strncmp("/bin/", process->argument[0], 5) != 0)
		tmp = ft_strjoin_lib("/bin/", process->argument[0]);
	else
		tmp = ft_strdup(process->argument[0]);
	if (execve(tmp, process->argument, env_mat) == -1)
	{
		free(tmp);
		perror("Error executing command with execve");
		exit(127);
	}
}

void	exec_pipe_loop(t_env_var **env, t_process_list *process, char **env_mat,
			int *pipe_fd)
{
	int		prev_fd;
	int		status;
	pid_t	pid;

	prev_fd = -1;
	status = 0;
	while (process)
	{
		if (g_status == 130 || process->heredoc == 1)
		{
			if (!process->next)
			{
				unlink("tmp_heredoc.txt");
				break ;
			}
			process = process->next;
		}
		if (process->next && pipe(pipe_fd) == -1)
			error_and_free("Error creating pipe", env_mat, 1, process->child);
		pid = fork();
		if (pid == -1)
			error_and_free("Error during fork", env_mat, 1, process->child);
		if (pid == 0)
			exec_child_process(process, env, prev_fd, pipe_fd);
		else
			close_and_update_fd(&prev_fd, pipe_fd);
		process = process->next;
	}
	while (wait(&status) > 0)
		;
	if (WIFEXITED(status))
		g_status = WEXITSTATUS(status);
}

void	ft_execute_pipe_line(t_env_var **env, t_process_list *process)
{
	char	**env_mat;
	int		pipe_fd[2];

	if (!process->argument)
		process = process->next;
	pipe_fd[0] = -1;
	pipe_fd[1] = -1;
	env_mat = ft_list_to_arr(*env);
	if (process->next == NULL && is_builtins(process->command) != 0)
	{
		handle_redirection(process);
		execute_command(process, env, env_mat);
		if (dup2(process->in_file, STDIN_FILENO) < 0)
			error_and_free("Error duplicating output file descriptor",
				env_mat, 1, process->child);
		if (dup2(process->out_file, STDOUT_FILENO) < 0)
			error_and_free("Error duplicating output file descriptor",
				env_mat, 1, process->child);
		process->in_file = 0;
		process->out_file = 1;
	}
	else
		exec_pipe_loop(env, process, env_mat, pipe_fd);
	free_matrix((void **)env_mat);
}
