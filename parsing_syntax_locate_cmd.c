#include "main.h"

char **get_path_from_env_lst(t_env *env_lst)
{
	char **path;

	while (env_lst)
	{
		if (!ft_strncmp(env_lst->key, "PATH", 5))
		{
			path = ft_split(env_lst->value, ':');
			break;
		}
		env_lst = env_lst->next;
	}
	return (path);
}

char *get_path_from_cmd(t_env *env_lst, char *cmd)
{
	int		i;
	char	**paths;
	char	*path;
	
	i = 0;
	paths = get_path_from_env_lst(env_lst);
	while (paths && paths[i])
	{
		path = ft_strjoin_with_slash(paths[i], cmd);
		if (!access(path, F_OK | X_OK))
		{
			strs_free(paths);
			return (path);
		}
		i++;
	}
	strs_free(paths);
	return (0);
}

int	locate_cmd(t_cmd *cmd, t_env *env_lst)
{
	char *path;
	
	if (!cmd->argv || !cmd->argv[0])
		return (0);
	str_to_lowercase(cmd->argv[0]);
	if (ft_strchr(cmd->argv[0], '/'))
		path = ft_strdup(cmd->argv[0]);
	else
		path = get_path_from_cmd(env_lst, cmd->argv[0]);
	if (path)
	{
		free(cmd->argv[0]);
		cmd->argv[0] = path;
	}
	else
		return (1);
	return (0);
}
