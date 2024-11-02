#include "../minishell.h"

int is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f' || c == '\v');
}
// prendo l'input e lo memorizo in una matrice , skippando gli eventuali spazi , manca la casistica delle virgolette
char **the_tokenizer(char *input)
{
	char **tokens = malloc(MAX_TOKENS * sizeof (char *));
	int token_count = 0;
	int i = 0;
	while(input[i] != '\0')
	{
		while(is_space(input[i]))
			i++;
		if(input[i] == '\0')
			break;
		tokens[token_count] = malloc(MAX_TOKEN_LEN * sizeof (char));
		int j = 0;

		while(input[i] != '\0' && !is_space(input[i]))
		{
			if(input[i++] == '"')
			{
				while(input[i] != '"' && input[i] != '\0')
				{
					if(input[++i] == '"')
					{
						tokens[token_count][j++] = input[i];
						tokens[token_count][j++] = '\0';
						break;
					}
					tokens[token_count][j++] = input[++i];
				}
			}
			j = 0;
			tokens[token_count][j++] = input[i++];
		}
		tokens[token_count][j] = '\0';
		token_count++;
	}
	tokens[token_count] = NULL;
	return (tokens);
}

void	signal_handle(int signal)
{
	if (signal == SIGINT)
	{
		// g_status = 130
		rl_replace_line("", 1);
		ft_putendl_fd("", STDOUT_FILENO);
		if (rl_on_new_line() == -1)
			exit (EXIT_FAILURE);
		rl_redisplay();
	}
}

int	main(int argc, char **argv,char **env)
{
	t_rline *line;
	int i = 0;
	int j = 0;
	if (argc != 1)
		return (printf("Error argc number\n"), 1);
	line = ft_calloc(1, sizeof(t_rline));
	while (1)
	{
		signal(SIGINT, signal_handle);
		signal(SIGQUIT, SIG_IGN);
		free(line->input);
		line->input = readline("minishell->");
		if (line->input == NULL)
		{
			free(line->input);
			clear_history();
			printf("End of input\n");
			break ;
		}
		add_history(line->input);
		line->mat_input = the_tokenizer(line->input);

	while(line->mat_input[i] != NULL)
	{
		printf("%s\n", line->mat_input[i]);
		i++;
	}
	}
}
