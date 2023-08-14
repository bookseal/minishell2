/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwonle2 <jiwonle2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 15:21:57 by jiwonle2          #+#    #+#             */
/*   Updated: 2023/08/14 18:58:06 by jiwonle2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	built_in_env(t_env **env_lst)
{
	t_env	*env;

	env = *env_lst;
	while (env)
	{
		if (env->tag)
		{
			env = env->next;
			continue ;
		}
		ft_putstr_fd(env->key, 1);
		ft_putstr_fd("=", 1);
		ft_putstr_fd(env->value, 1);
		ft_putendl_fd("", 1);
		env = env->next;
	}
	return (0);
}
