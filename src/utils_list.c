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
	extern char **environ;

	for (int i = 0; environ[i] != NULL; i++)
	{
		char *env_entry = ft_strdup_lib(environ[i]); // Copia l'entry di ambiente
		char **name_value = ft_split(env_entry, "=");

		if (name_value[0] && name_value[1]) // Se entrambi name e value esistono
		{
			t_env_var *new_var = create_env_node(name_value[0], name_value[1]);
			add_env_var(env_list, new_var);
		}
		// free(name_value[0]);
		// free(name_value[1]);
		// free(name_value);
		// free(env_entry);
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

void env_storage(char **environ, t_env_var **list)
{
	if (!environ || !list)
		return;

	for (int i = 0; environ[i] != NULL; i++) {
        // Trova il segno "=" per separare il nome e il valore
		char *equal_sign = strchr(environ[i], '=');
		if (!equal_sign)
			continue; // salta se non c'è "=" nella stringa

        // Calcola la lunghezza di name e value
		size_t name_len = equal_sign - environ[i];
		const char *name = strndup(environ[i], name_len);
		const char *value = strdup(equal_sign + 1);

        // Crea un nuovo nodo e inseriscilo nella lista
		t_env_var *node = create_env_node(name, value);
		if (!node) {
			free((void*)name);
			free((void*)value);
			continue; // Salta in caso di errore
		}

		node->next = *list;
		*list = node;

		//free((void*)name);
		//free((void*)value);
	}
}
