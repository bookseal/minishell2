#include "main.h"

void	unnecessary_env_delete(t_env **env_lst)
{
	t_env	*env;
	t_env	*tmp;
	t_env	*prev;

	env = *env_lst;
	prev = 0;
	while (env)
	{
		tmp = env->next;
		if (env->need_to_del)
		{
			if (prev != NULL)
				prev->next = tmp;
			else
				*env_lst = tmp;
			env_delone(env, &free);
		}
		else
			prev = env;
		env = tmp;
	}
}

void	del_env(char *key, t_env **env_lst)
{
	t_env	*env;

	env = *env_lst;
	while (env)
	{
		if (!ft_strncmp(key, env->key, ft_strlen(key) + 1))
		{
			env->need_to_del = TRUE;
			unnecessary_env_delete(env_lst);
			break ;
		}
		env = env->next;
	}
}

int	unset_envs(t_cmd *cmd, t_env **env_lst)
{
	int		res;
	int		i;
	char	*key;

	res = 0;
	i = 1;
	while (cmd->argv[i] != NULL)
	{
		key = cmd->argv[i];
		res = is_key_name_error(key);
		if (res)
			return (1);
		del_env(key, env_lst);
		i++;
	}
	return (res);
}

int	built_in_unset(t_cmd *cmd, t_env **env_lst)
{
	int	res;

	res = 0;
	if (!env_lst || !cmd)
		return (1);
	if (!cmd->argv[1])
		return (1);
	return (unset_envs(cmd, env_lst));
}
