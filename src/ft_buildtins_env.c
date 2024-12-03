#include "../minishell.h"

// print all the env_list

void	ft_env(t_env_var *env)
{
    t_env_var *current;

	current = env;
    while (current != NULL)
	{
        printf("%s=%s\n", current->name, current->value);
        current = current->next;
    }
}

void	ft_unset(t_env_var **env, char *str)
{
	t_env_var *prev;
	t_env_var *curr;

	prev = NULL;
	curr = *env;
	while (curr)
	{
		if (ft_strncmp(str, curr->name, ft_strlen_lib(curr->name)) == 0)
		{
			if (prev)
				prev->next = curr->next;
			else
				*env = curr->next;
			free(curr->name);
			free(curr->value);
			free(curr);
			break;
		}
		prev = curr;
		curr = curr->next;
	}
}

void	ft_export(t_process_list **info_process, t_env_var **env)
{
	int			i;
	char		*str_name;
	char		*str_value;
	t_env_var	*tmp;

	i = 0;
	str_name = NULL;
	str_value = NULL;
	tmp = *env;
	while ((*info_process)->argument[1][i] && (*info_process)->argument[1][i] != '=')
		i++;
	if ((*info_process)->argument[1][i] != '=')
		return ;
	str_name = ft_substr_lib((*info_process)->argument[1], 0, i);
	str_value = ft_substr_lib((*info_process)->argument[1], i + 1, ft_strlen_lib((*info_process)->argument[1]) - i + 1);
	while (tmp)
	{
		if (ft_strncmp(str_name, (tmp)->name, ft_strlen_lib((tmp)->name)) == 0)
		{
			free((tmp)->value);
			(tmp)->value = ft_strdup_lib(str_value);
			free(str_value);
			return (free(str_name));
		}
		tmp = (tmp)->next;
	}
	ft_add_env_var(env, ft_create_env_node(str_name, str_value));
}