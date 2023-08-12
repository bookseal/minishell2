/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_env_lst_to_envp.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gichlee <gichlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 22:12:41 by gichlee           #+#    #+#             */
/*   Updated: 2023/08/12 22:14:16 by gichlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	get_envp_size(t_env *env_lst)
{
	t_env	*env;
	int		envp_size;
	
	env = env_lst;
	envp_size = 0;
	while (env)
	{
		if (env->tag)
		{
			env = env->next;
			continue ;
		}
		env = env->next;
		envp_size++;
	}
	return (envp_size);
}

int	env_lst_to_envp(t_env *env_lst, char ***envp)
{
	int		envp_size;
	t_env	*env;
	int		i;

	envp_size = get_envp_size(env_lst);
	*envp = ft_calloc(envp_size + 2, sizeof(char **));
	env = env_lst;
	i = 0;
	while (i < envp_size)
	{
		if (env->tag)
		{
			env = env->next;
			continue ;
		}
		(*envp)[i] = ft_strjoin_with_sep(env->key, env->value, "=");
		i++;
		env = env->next;
	}
	return (0);
}
