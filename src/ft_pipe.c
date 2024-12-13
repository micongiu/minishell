#include "../minishell.h"

int ft_count_node(t_env_var *env)
{
	int i;

	i = 0;

	while(env)
	{
		i++;
		env = env->next;
	}
	return(i);
}
char **ft_list_to_arr(t_env_var *env_h)
{
	char **mat;
	int i;
	char *c;

	c = "=";
	i = 0;
	mat = malloc((ft_count_node(env_h) + 1) * sizeof(char*));
	while(env_h)
	{
		mat[i] = ft_strjoin_lib(env_h->name, c);
		mat[i] = ft_strjoin_lib(mat[i], env_h->value);
		i++;
		env_h = env_h->next;
	}
	mat[i] = NULL;
	// i = 0;
	// while(mat[i])
	// {
	// 	printf("%s\n", mat[i]);
	// 	i++;
	// }
	return(mat);
}

void	ft_execute_pipe_line(t_env_var *env, t_process_list *process)
{
	char **mat; //env convertita in matrice easy
	int pipe_fd[2];
	int prev_fd = 0;
	pid_t pid;

	mat = ft_list_to_arr(env);
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
			if(execve(process->command, process->argument, mat) == -1)
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
}
