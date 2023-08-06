#include "main.h"

int print_env_lst(t_env **env_lst, int is_export)
{
	t_env *env;

	env = *env_lst;
	while (env)
	{
		if (is_export)
			ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(env->key, 1);
		ft_putstr_fd("=", 1);
		if (is_export)
			ft_putstr_fd("\"", 1);
		ft_putstr_fd(env->value, 1);
		if (is_export)
			ft_putstr_fd("\"", 1);
		ft_putendl_fd("", 1);
		env = env->next;
	}
	return (0);
}

int	built_in_env(t_env **env_lst)
{
	return (print_env_lst(env_lst, FALSE));
}
