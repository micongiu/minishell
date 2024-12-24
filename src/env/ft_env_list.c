#include "../../minishell.h"

// This function retrieves a node from the environment list based on a given key.
t_env_var	*get_node_of(t_env_var **env_list, char *key)
{
	t_env_var	*current;

	if (!env_list || !key)
		return (NULL);
	current = *env_list;
	while (current)
	{
		if (ft_strncmp(current->name, key, ft_strlen_lib(key)) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}

void	ft_add_env_var(t_env_var **env_list, char *name, char *value)
{
	t_env_var	*temp;
	t_env_var	*new_var;

	new_var = (t_env_var *)ft_calloc(1, sizeof(t_env_var));
	if (!new_var)
		return ;
	new_var->name = ft_strdup_lib(name);
	new_var->value = ft_strdup_lib(value);
	new_var->next = NULL;
	free(name);
	free(value);
	temp = *env_list;
	if (!env_list)
		return ;
	if (!*env_list)
		*env_list = new_var;
	else
	{
		while (temp->next)
			temp = temp->next;
		temp->next = new_var;
	}
}

char	*ft_save_value(t_var_count count, char **env, char *str_name)
{
	char	*tmp_str;
	char	*str_value;

	str_value = NULL;
	tmp_str = NULL;
	str_value = (char *)ft_calloc(ft_strlen_lib(env[count.i]) - count.k + 1,
			sizeof(char));
	count.j = 0;
	count.k++;
	while (str_value && env[count.i][count.k])
		str_value[count.j++] = env[count.i][count.k++];
	str_value[count.j] = '\0';
	if (ft_strncmp(str_name, "SHLVL", ft_strlen_lib(str_name)) == 0)
	{
		tmp_str = ft_itoa(ft_atoi(str_value) + 1);
		free(str_value);
		str_value = tmp_str;
	}
	return (str_value);
}

void	ft_init_env_list(t_env_var **env_list, char **env)
{
	t_var_count	count;
	char		*str_name;
	char		*str_value;

	str_value = NULL;
	str_name = NULL;
	count.i = 0;
	count.j = 0;
	count.k = 0;
	while (env[count.i])
	{
		count.k = 0;
		while (env[count.i][count.k] && env[count.i][count.k] != '=')
			count.k++;
		str_name = (char *)ft_calloc(count.k + 1, sizeof(char));
		ft_strlcpy(str_name, env[count.i], count.k + 1);
		str_value = ft_save_value(count, env, str_name);
		ft_add_env_var(env_list, str_name, str_value);
		count.i++;
	}
}

void	free_env_list(t_env_var **cur)
{
	t_env_var	*tmp;

	tmp = NULL;
	while (*cur != NULL)
	{
		tmp = (*cur)->next;
		free((*cur)->name);
		free((*cur)->value);
		free(*cur);
		*cur = tmp;
	}
}
