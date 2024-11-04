#include "../minishell.h"

t_env_var *create_env_node(const char *name, const char *value)
{
	t_env_var *new_var = malloc(sizeof(t_env_var));
	if (!new_var)
		return NULL;
	new_var->name = ft_strdup_lib(name);
	new_var->value = ft_strdup_lib(value);
	new_var->next = NULL;
	return new_var;
}

void add_env_var(t_env_var **env_list, t_env_var *new_var)
{
	if (!*env_list)
		*env_list = new_var;
	else
	{
		t_env_var *temp = *env_list;
		while (temp->next)
			temp = temp->next;
		temp->next = new_var;
	}
}


void init_env_list(t_env_var **env_list)
{
	extern char **environ;

	for (int i = 0; environ[i] != NULL; i++)
	{
		char *env_entry = ft_strdup_lib(environ[i]);
		char **name_value = ft_split(env_entry, "=");
		if (name_value[0] && name_value[1])
		{
			t_env_var *new_var = create_env_node(name_value[0], name_value[1]);
			add_env_var(env_list, new_var);
		}
	}
}


void env_storage(char **environ, t_env_var **list)
{
	int i;
	i = -1;
	if (!environ || !list)
		return;

	while (environ[++i] != NULL)
	{
		char *equal_sign = strchr(environ[i], '=');
		if (!equal_sign)
			continue;
		size_t name_len = equal_sign - environ[i];
		const char *name = strndup(environ[i], name_len);
		const char *value = strdup(equal_sign + 1);
		t_env_var *node = create_env_node(name, value);
		if (!node)
		{
			free((void*)name);
			free((void*)value);
			continue;
		}
		node->next = *list;
		*list = node;
	}
}
