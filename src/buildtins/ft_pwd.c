#include "../../minishell.h"

void	pwd_directory(t_env_var **env_list, int fd)
{
	t_env_var	*env;

	env = *env_list;
	env = get_node_of(env_list, "PWD");
	ft_putendl_fd(env->value, fd);
}
