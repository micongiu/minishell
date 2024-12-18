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
	char	**env_mat;
	char	*bin_path;
	int		pipe_fd[2];
	int		prev_fd = 0;
	pid_t	pid;

	env_mat = ft_list_to_arr(*env);
	bin_path = ft_strjoin_lib("/bin/", process->command);
	free(process->argument[0]);
	process->argument[0] = ft_strdup(bin_path);
	free(bin_path);
	// execute_command(process, env, env_mat);
	// free_matrix((void **)env_mat);
	// return ;
	while(process)
	{
		if(process->next)
		{
			if(pipe(pipe_fd) == -1)
				perror("err_create_pipe\n");
		}
		pid = fork();
		if(pid == -1)
			printf("err_fork\n");
		if(pid == 0)
		{
			if(prev_fd)
			{
				if(dup2(prev_fd, STDIN_FILENO) == -1)
					printf("err_dup2_STDION\n");
				close(prev_fd);
			}
			if(process->next)
			{
				if(dup2(pipe_fd[1], STDOUT_FILENO) == -1)
					printf("err_dup2_STDOUT\n");
				close(pipe_fd[0]);
				close(pipe_fd[1]);
			}
			execute_command(process, env, env_mat);
			printf("#####err_execve\n");
		}
		else
		{
			if(prev_fd)
				close(prev_fd);
			close(pipe_fd[1]);
			prev_fd = pipe_fd[0];
		}
		waitpid(pid,NULL,0);
		process = process->next;
	}
	free_matrix((void **)env_mat);
}
