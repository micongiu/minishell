#include "../minishell.h"

extern char **environ;

t_env_var *create_env_var(const char *name, const char *value)
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
	if (!*env_list) {
		*env_list = new_var;
	} else {
		t_env_var *temp = *env_list;
		while (temp->next) {
			temp = temp->next;
		}
		temp->next = new_var;
	}
}


void init_env_list(t_env_var **env_list)
{
	for (int i = 0; environ[i] != NULL; i++)
	{
		char *env_entry = strdup(environ[i]);
		char *name = strtok(env_entry, "=");
		char *value = strtok(NULL, "");

	if (name && value)
	{
		t_env_var *new_var = create_env_var(name, value);
		add_env_var(env_list, new_var);
	}
	free(env_entry);
	}
}

void free_env_list(t_env_var *env_list)
{
	t_env_var *temp;
	while (env_list)
	{
		temp = env_list;
		env_list = env_list->next;
		free(temp->name);
		free(temp->value);
		free(temp);
	}
}

