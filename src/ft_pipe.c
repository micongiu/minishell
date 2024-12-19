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

void	ft_execute_pipe_line(t_env_var **env, t_process_list *process)
{
	char **mat; //env convertita in matrice easy
	char *bin_path;
	int pipe_fd[2];
	int prev_fd = 0;
	pid_t pid;

	mat = ft_list_to_arr(*env);
	bin_path = ft_strjoin_lib("/bin/", process->command);
	free(process->argument[0]);
	process->argument[0] = ft_strdup(bin_path);
	free(bin_path);
	while (process)
	{
		if (process->next)
		{
			if (pipe(pipe_fd) == -1)
			{
				perror("Error creating pipe");
				exit(EXIT_FAILURE);
			}
		}
		pid = fork();
		if (pid == -1)
		{
			perror("Error during fork");
			exit(EXIT_FAILURE);
		}

		if (pid == 0) // Child process
		{
			printf("==== Child process PID = %i\n", getpid());
			if (prev_fd)
			{
				if (dup2(prev_fd, STDIN_FILENO) == -1)
				{
					perror("Error duplicating STDIN");
					exit(EXIT_FAILURE);
				}
				close(prev_fd);
			}
			if (process->next)
			{
				if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
				{
					perror("Error duplicating STDOUT");
					exit(EXIT_FAILURE);
				}
			}
			close(pipe_fd[0]);
			close(pipe_fd[1]);
			if ((ft_strncmp(process->command, "cd", 3) == 0) || 
				(ft_strncmp(process->command, "pwd", 4) == 0) || 
				(ft_strncmp(process->command, "echo", 5) == 0) || 
				(ft_strncmp(process->command, "env", 4) == 0) || 
				(ft_strncmp(process->command, "export", 7) == 0) || 
				(ft_strncmp(process->command, "unset", 6) == 0))
				execute_command(process, &*env, mat);
			else
			{
				execve(process->command, process->argument, mat);
				perror("Error executing command with execve");
				exit(EXIT_FAILURE);
			}
		}
		else // Parent process
		{
			printf("==== Parent process PID = %i\n", getpid());
			if (prev_fd)
				close(prev_fd); // Close previous pipe read end
			close(pipe_fd[1]); // Close current pipe write end
			prev_fd = pipe_fd[0]; // Save current pipe read end for next process
		}
		waitpid(pid,NULL,0);
		process = process->next;
		}
		free_matrix((void *) mat);
}
