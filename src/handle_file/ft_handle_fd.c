/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmedyns <anmedyns@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 16:37:44 by anmedyns          #+#    #+#             */
/*   Updated: 2024/12/30 17:12:03 by anmedyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

extern int	g_status;

void	close_and_update_fd(int *prev_fd, int *pipe_fd)
{
	if (*prev_fd != -1)
		close(*prev_fd);
	if (pipe_fd[1] != -1)
		close(pipe_fd[1]);
	*prev_fd = pipe_fd[0];
}

void	handle_input_redirection(t_process_list *process)
{
	int	fd;

	fd = open(process->file_fd, O_RDONLY);
	if (fd < 0)
		error_and_free("Error opening input file", NULL, 1, process->child);
	if (dup2(fd, STDIN_FILENO) < 0)
		error_and_free("Error duplicating input file descriptor",
			NULL, 1, process->child);
	close(fd);
}

void	handle_output_redirection(t_process_list *process)
{
	int	fd;

	fd = open(process->file_fd, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		error_and_free("Error opening output file", NULL, 1, process->child);
	if (dup2(fd, STDOUT_FILENO) < 0)
		error_and_free("Error duplicating output file descriptor",
			NULL, 1, process->child);
	close(fd);
}

void	handle_append_redirection(t_process_list *process)
{
	int	fd;

	fd = open(process->file_fd, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		error_and_free("Error opening output file in append mode",
			NULL, 1, process->child);
	if (dup2(fd, STDOUT_FILENO) < 0)
		error_and_free("Error duplicating output file descriptor",
			NULL, 1, process->child);
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
