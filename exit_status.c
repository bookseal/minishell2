/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gichlee <gichlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 21:53:43 by gichlee           #+#    #+#             */
/*   Updated: 2023/08/14 19:48:02 by gichlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_exit_status(t_env **env_lst, unsigned int *status)
{
	t_env	*env;

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
	t_env	*env;

	env = *env_lst;
	while (env && env->tag != ENV_EXIT)
		env = env->next;
	if (!env)
	{
		env = env_lstnew_malloc("?", "?");
		env->tag = ENV_EXIT;
		env_lstadd_back(env_lst, env);
	}
	env->exit_status = status;
	return (0);
}
