/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal_handle.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmedyns <anmedyns@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 16:12:22 by anmedyns          #+#    #+#             */
/*   Updated: 2024/12/30 17:12:52 by anmedyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

extern int	g_status;

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
