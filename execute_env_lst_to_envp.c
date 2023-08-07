#include "main.h"

int	env_lst_to_envp(t_env *env_lst, char **envp)
{
	int	envp_size;
	t_env	*env;
	int	i;

	env = env_lst;
	envp_size = 0;
	while (env)
	{
		if (env->tag)
		{
			env = env->next;
			continue;
		}
		env = env->next;
		envp_size++;
	}
	envp = ft_calloc(envp_size + 2, sizeof(char *));
	env = env_lst;
	i = 0;
	while (i < envp_size)
	{
		if (env->tag)
		{
			env = env->next;
			continue;
		}
		envp[i] = ft_strjoin_with_sep(env->key, env->value, "=");
		i++;
		env = env->next;
	}
	return (0);
}