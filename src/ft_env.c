#include "../minishell.h"

t_env_var *create_env_node(char *name, char *value)
{
	t_env_var *new_var;
	
	new_var = (t_env_var *)ft_calloc(1, sizeof(t_env_var));
	if (!new_var)
		return (NULL);
	new_var->name = ft_strdup_lib(name);
	new_var->value = ft_strdup_lib(value);
	new_var->next = NULL;
	return (new_var);
}

void add_env_var(t_env_var **env_list, t_env_var *new_var)
{
	t_env_var *temp;

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

void init_env_list(t_env_var **env_list, char **env)
{
	int			i;
	char		**name_value;

	name_value = NULL;
	i = 0;
	while (env[i])
	{
		name_value = ft_split(env[i], '=');
		add_env_var(env_list, create_env_node(name_value[0], name_value[1]));
		free_matrix((void **)name_value);
		i++;
	}
}

void free_env_list(t_env_var **cur)
{
	t_env_var *tmp;

	while (*cur != NULL)
	{
		tmp = (*cur)->next;
		free((*cur)->name);
		free((*cur)->value);
		free(*cur);
		*cur = tmp;
	}
}
