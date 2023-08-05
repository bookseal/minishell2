#include "main.h"

int get_from_env(t_env *env_lst)
{
	while (env_lst != 0)
	{
		// If the current variable is PWD, print its value
		if (ft_strncmp(env_lst->key, "PWD", 4) == 0)
		{
			ft_putstr_fd(env_lst->value, 1);
			ft_putchar_fd('\n', 1);
			return (1);
		}
		env_lst = env_lst->next;
	}
	return (0);
}

int get_pwd_str(t_env **env_lst, char **pwd)
{
	t_env	*env;

	env = *env_lst;
	while (env != 0)
	{
		if (!ft_strncmp(env->key, "PWD", 4))
		{
			*pwd = ft_strdup(env->value);
			break;
		}
		env = env->next;
	}
	if (!env)
		return (1);
	return (0);
}

int built_in_pwd(t_env **env_lst)
{
	char *pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		if (get_pwd_str(env_lst, &pwd))
			return (print_error(NULL, "not found PWD"));
	}
	ft_putendl_fd(pwd, 1);
	free(pwd);
	return (0);
}
