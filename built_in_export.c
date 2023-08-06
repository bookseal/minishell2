#include "main.h"

void new_env(t_env **env_lst, char *key, char *value)
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
		if (!((key[i] >= 48 && key[i] <= 57) || (key[i] == '_') || ft_isalpha(key[i])))
			return (print_error(0, "NOT VALID KEY"));
		i++;
	}
	return (0);
}

int update_env(char *str, int *res, t_env **env_lst)
{
	char	*delimiter;
	char	*key;
	char	*value;

	delimiter = ft_strchr(str, '=');
	if (delimiter)
	{
		*delimiter = '\0';
		key = ft_strdup(str);
		value = ft_strdup(str + ft_strlen(key) + 1);
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
		print_env_lst(env_lst, TRUE);
		return (0);
	}
	i = 1;
	while (cmd->argv[i] != 0)
	{
		update_env(cmd->argv[i], &res, env_lst);
		i++;
	}
	return (0);
}
