#include "../../minishell.h"

void	ft_pwd(t_env_var **env_list)
{
	t_env_var	*env;

	env = *env_list;
	env = get_node_of(env_list, "PWD");
	ft_putendl_fd(env->value, STDOUT_FILENO);
}
