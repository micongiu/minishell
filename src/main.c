/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmedyns <anmedyns@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 16:01:48 by micongiu          #+#    #+#             */
/*   Updated: 2024/12/30 16:57:04 by anmedyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_execute_minishell(t_env_var *env_list,
			t_process_list **head_process)
{
	char	*input;

	while (1)
	{
		*head_process = NULL;
		signal(SIGINT, ft_signal_handle);
		signal(SIGQUIT, SIG_IGN);
		input = readline("minishell->");
		if (input == NULL)
		{
			ft_exit(input, &env_list, head_process, NULL);
			return ;
		}
		if (ft_strlen_lib(input) > 0)
		{
			add_history(input);
			*head_process = ft_init_process_list
				(ft_tokenizer(input, env_list));
			ft_execute_pipe_line(&env_list, *head_process);
		}
		if (*head_process)
			free_process_list(head_process);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_env_var		*env_list;
	t_process_list	*head_process;

	env_list = NULL;
	head_process = NULL;
	env_list = NULL;
	if (argc != 1 && argv[0] == NULL)
		return (printf("Error argc number\n"), 1);
	ft_init_env_list(&env_list, env);
	ft_execute_minishell(env_list, &head_process);
	return (0);
}
