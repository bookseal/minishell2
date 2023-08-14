/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwonle2 <jiwonle2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 15:21:44 by jiwonle2          #+#    #+#             */
/*   Updated: 2023/08/14 18:57:59 by jiwonle2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_home_str(t_env **env_lst, char **home_str)
{
	t_env	*env;

	env = *env_lst;
	while (env != 0)
	{
		if (!ft_strncmp(env->key, "HOME", 5))
		{
			*home_str = ft_strdup(env->value);
			break ;
		}
		env = env->next;
	}
	if (!env)
		return (print_error(NULL, "not found HOME"));
	return (0);
}

int	built_in_cd(t_cmd *cmd, t_env **env_lst)
{
	char	*path;
	int		res;

	res = 0;
	if (!cmd->argv[1])
		res = get_home_str(env_lst, &path);
	else
		path = ft_strdup(cmd->argv[1]);
	if (res)
		return (res);
	res = go_to_path(path, env_lst);
	return (res);
}
