/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_syntax_locate_cmd.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gichlee <gichlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 18:26:58 by gichlee           #+#    #+#             */
/*   Updated: 2023/08/12 16:06:23 by gichlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		path = ft_strjoin_with_sep(paths[i], cmd, "/");
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
	{
		path = ft_strdup(cmd->argv[0]);
		if (access(path, F_OK | X_OK))
		{
			free(path);
			print_error(0, "command not found");
			return (update_exit_status(&env_lst, 127));
		}
	}
	else
		path = get_path_from_cmd(env_lst, cmd->argv[0]);
	if (path)
	{
		free(cmd->argv[0]);
		cmd->argv[0] = path;
		cmd->is_cmd = 1;
	}
	else
	{
		print_error(0, "command not found");
		return (update_exit_status(&env_lst, 127));
	}
	return (0);
}
