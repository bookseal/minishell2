#include "main.h"

int print_env_lst(t_env **env_lst)
{
	t_env *env;

	while (env)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(env->key, 1);
		ft_putstr_fd("=", 1);
		ft_putendl_fd(env->value, 1);
		env = env->next;
	}
	return (0);
}

t_env *new_env(t_env **env_lst, char *key, char *value)
{
	t_env	*env;

	if (!value)
		value = ft_calloc(1, sizeof(char));
	env = *env_lst;
	while (env != 0)
	{
		if (!ft_strncmp(env->key, key, ft_strlen(env->key) + 1))
		{
			free(env->value);
			env->value = ft_strdup(value);
			break ;
		}
		env = env->next;
	}
	if (!env)
	{
		env = env_lstnew_malloc(key, value);
		env_lstadd_back(env_lst, env);
	}
	return (env);
}

int	is_key_name_error(char *key)
{
	int		i;

	if (!((key[0] == '_') || ft_isalpha(key[0])))
		return (print_error(0, "NOT VALID KEY"));
	if (ft_strlen(key) ==  1)
		return (0);
	i = 1;
	while (key[i] != '\0')
	{
		if ((key[i] >= 48 && key[i] <= 57) || (key[i] == '_') || ft_isalpha(key[i]))
			continue ;
		else
			return (print_error(0, "NOT VALID KEY"));
		i++;
	}
	return (0);
}

int update_env(t_cmd *cmd, int i, int *res, t_env **env_lst)
{
	char	*delimiter;
	char	*key;
	char	*value;

	if (ft_strchr(cmd->argv[i] + 1, '='))
	{
		delimiter = ft_strchr(cmd->argv[i], '=');
		*delimiter = '\0';
		key = ft_strdup(cmd->argv[i]);
		value = ft_strdup(cmd->argv[i] + ft_strlen(key) + 1);
		if (!is_key_name_error(key))
			new_env(env_lst, key, value);
		free(key);
		free(value);
		return (0);
	}
	if (!is_key_name_error(key))
			return (1);
	new_env(env_lst, key, 0);
	return (0);
}

int built_in_export(t_cmd *cmd, t_env **env_lst)
{
	int	i;
	int	res;

	res = 0;
	if (!cmd->argv[1])
	{
		print_env_lst(env_lst);
		return (0);
	}
	i = 0;
	while (cmd->argv[++i] != 0)
		update_env(cmd, i, &res, env_lst);
	return (0);
}
