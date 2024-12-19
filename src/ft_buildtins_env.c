#include "../minishell.h"

// print all the env_list

void	ft_env(t_env_var *env, int fd)
{
	t_env_var	*current;

	current = env;
	while (current != NULL)
	{
		ft_putstr_fd(current->name, fd);
		ft_putchar_fd('=', fd);
		ft_putstr_fd(current->value, fd);
		ft_putchar_fd('\n', fd);
		current = current->next;
	}
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
	}
}

void	ft_export_utility(t_env_var *tmp, char *str_name, char *str_value,
		t_env_var **env)
{
	char	*new_str_name;
	char	*new_str_value;

	new_str_name = NULL;
	new_str_value = NULL;
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
	new_str_name = remove_quotes(str_name);
	new_str_value = remove_quotes(str_value);
	ft_add_env_var(env, ft_create_env_node(new_str_name, new_str_value));
	free(str_name);
	free(str_value);
}

void	ft_export_null(t_env_var *env, int fd)
{
	t_env_var	*current;

	current = env;
	while (current != NULL)
	{
		ft_putstr_fd("declare -x ", fd);
		ft_putstr_fd(current->name, fd);
		ft_putchar_fd('=', fd);
		ft_putstr_fd(current->value, fd);
		ft_putchar_fd('\n', fd);
		current = current->next;
	}
}

void	ft_export(t_process_list **info_process, t_env_var **env, int fd)
{
	int			i;
	char		*str_name;
	char		*str_value;
	t_env_var	*tmp;

	i = 0;
	str_name = NULL;
	str_value = NULL;
	tmp = *env;
	if ((*info_process)->argument[1] == NULL)
	{
		ft_export_null((*env), fd);
		return ;
	}
	while ((*info_process)->argument[1][i]
			&& (*info_process)->argument[1][i] != '=')
		i++;
	if ((*info_process)->argument[1][i] != '=')
		return ;
	str_name = ft_substr_lib((*info_process)->argument[1], 0, i);
	str_value = ft_substr_lib((*info_process)->argument[1], i + 1,
			ft_strlen_lib((*info_process)->argument[1]) - i + 1);
	ft_export_utility(tmp, str_name, str_value, env);
}
