/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmedyns <anmedyns@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 16:36:48 by anmedyns          #+#    #+#             */
/*   Updated: 2024/12/30 17:12:26 by anmedyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

extern int	g_status;

static size_t	keyword_len(char *keyword)
{
	return (ft_strlen_lib(keyword));
}

static char	*handle_end_of_file(char *keyword, char *heredoc_content)
{
	printf("bash: warning: here-document at line delimited \
		by end-of-file (wanted `%s')\n", keyword);
	return (heredoc_content);
}

static char	*update_heredoc_content(char *heredoc_content, char *temp_line)
{
	char	*new_content;

	if (!heredoc_content)
		return (ft_strdup(temp_line));
	new_content = ft_strjoin(heredoc_content, temp_line);
	return (new_content);
}

char	*get_heredoc(char *keyword)
{
	char	*line;
	char	*heredoc_content;
	char	*temp_line;

	line = NULL;
	heredoc_content = NULL;
	while (g_status != 130)
	{
		line = readline("> ");
		if (!line)
			return (handle_end_of_file(keyword, heredoc_content));
		if (ft_strncmp(line, keyword, keyword_len(keyword)) == 0
			&& ft_strlen_lib(line) == keyword_len(keyword))
			return (free(line), heredoc_content);
		temp_line = ft_strjoin(line, "\n");
		if (!temp_line)
			return (heredoc_content);
		heredoc_content = update_heredoc_content(heredoc_content, temp_line);
		free(temp_line);
	}
	return (heredoc_content);
}

char	*ft_heredoc(char *keyword, t_process_list *process)
{
	char	*line;
	int		fd;

	line = NULL;
	signal(SIGINT, ft_signal_heredoc);
	if (!keyword[0])
	{
		process->heredoc = 1;
		g_status = 2;
		printf("Syntax error near unexpected token `<<'\n");
		return (NULL);
	}
	line = get_heredoc(keyword);
	fd = open("tmp_heredoc.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (line)
	{
		write(fd, line, ft_strlen_lib(line));
		free(line);
	}
	close(fd);
	signal(SIGINT, ft_signal_handle);
	if (g_status == 130)
		return(unlink("tmp_heredoc.txt"), NULL);
	return ("tmp_heredoc.txt");
}
