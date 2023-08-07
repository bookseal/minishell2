#include "main.h"

int	is_exit_status(t_env **env_lst, int *status)
{
	t_env *env;

	env = *env_lst;
	while (env && env->tag != ENV_EXIT)
		env = env->next;
	if (ft_strncmp(env->value, "?", 1))
	{
		free(env->value);
		env->value = ft_strdup("?");
		*status = env->exit_status;
		return (1);
	}
	*status = env->exit_status;
	return (0);
}

int	update_exit_status(t_env **env_lst, int status)
{
	t_env *env;

	env = *env_lst;
	while (env && env->tag != ENV_EXIT)
		env = env->next;
	if (!env)
	{
		env = env_lstnew_malloc("?", "?");
		env_lstadd_back(env_lst, env);
		env->tag = ENV_EXIT;
	}
	env->exit_status = status;
	return (0);
}
