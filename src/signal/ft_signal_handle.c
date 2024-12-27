/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal_handle.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: micongiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 16:06:05 by micongiu          #+#    #+#             */
/*   Updated: 2024/12/27 16:06:06 by micongiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	g_status;

void	ft_signal_handle(int signal)
{
	if (signal == SIGINT)
	{
		g_status = 130;
		rl_replace_line("", 1);
		ft_putendl_fd("", 1);
		if (rl_on_new_line() == -1)
			exit (EXIT_FAILURE);
		rl_redisplay();
	}
}

void	ft_signal_heredoc(int signal)
{
	if (signal == SIGINT)
		g_status = 130;
}
