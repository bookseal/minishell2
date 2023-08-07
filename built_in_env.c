#include "main.h"

int	built_in_env(t_env **env_lst)
{
	t_env *env;

	env = *env_lst;
	while (env)
	{
		if (env->tag)
		{
			env = env->next;
			continue;
		}
		ft_putstr_fd(env->key, 1);
		ft_putstr_fd("=", 1);
		ft_putstr_fd(env->value, 1);
		ft_putendl_fd("", 1);
		env = env->next;
	}
	return (0);
}
