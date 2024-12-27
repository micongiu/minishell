#include "../../minishell.h"

void	check_for_status(t_env_var *curr)
{
	if (curr->next == NULL)
		g_status = 0;
}

void	ft_unset(t_env_var **env, char *str)
{
	t_env_var	*prev;
	t_env_var	*curr;
	char		*new_str;

	prev = NULL;
	curr = *env;
	new_str = remove_quotes(str);
	while (curr)
	{
		if (ft_strncmp(new_str, curr->name, ft_strlen_lib(curr->name)) == 0)
		{
			if (prev)
				prev->next = curr->next;
			else
				*env = curr->next;
			free(curr->name);
			free(curr->value);
			free(curr);
			free(new_str);
			break ;
		}
		prev = curr;
		curr = curr->next;
		check_for_status(curr);
	}
}
