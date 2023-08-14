/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gichlee <gichlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 15:22:54 by jiwonle2          #+#    #+#             */
/*   Updated: 2023/08/14 20:02:39 by gichlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	new_env(t_env **env_lst, char *key, char *value)
{
	t_env_tag	tag;
	t_env		*env;
	int			check;

	check = 0;
	tag = NO_ENV_TAG;
	if (!value)
	{
		value = ft_calloc(1, sizeof(char));
		tag = ENV_NO_VALUE;
		check = 1;
	}
	env = *env_lst;
	new_env_util(&env, key, value, tag);
	if (!env)
	{
		env = env_lstnew_malloc(key, value);
		env->tag = tag;
		env_lstadd_back(env_lst, env);
	}
	if (check)
		free(value);
}

int	is_key_name_error(char *key)
{
	int		i;

	if (!((key[0] == '_') || ft_isalpha(key[0])))
		return (print_error(0, "NOT VALID KEY"));
	if (ft_strlen(key) == 1)
		return (0);
	i = 1;
	while (key[i] != '\0')
	{
		if (!((key[i] >= 48 && key[i] <= 57) || (key[i] == '_')
				|| ft_isalpha(key[i])))
			return (print_error(0, "NOT VALID KEY"));
		i++;
	}
	return (0);
}

int	update_env(char *str, t_env **env_lst)
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
	if (!is_key_name_error(str))
		new_env(env_lst, str, 0);
	return (0);
}

void	print_env_lst_export(t_env **env_lst)
{
	t_env	*new_env_lst;
	t_env	*env;

	new_env_lst = env_dup(*env_lst);
	env = new_env_lst;
	while (env)
	{
		if (env->tag == ENV_EXIT)
		{
			env = env->next;
			continue ;
		}
		print_export_util("declare -x ", env->key);
		if (env->tag == ENV_NO_VALUE)
		{
			ft_putendl_fd("", 1);
			env = env->next;
			continue ;
		}
		print_export_util("=", "\"");
		print_export_util(env->value, "\"");
		ft_putendl_fd("", 1);
		env = env->next;
	}
	env_lstclear(&new_env_lst, &free);
}

int	built_in_export(t_cmd *cmd, t_env **env_lst)
{
	int	i;
	int	res;

	res = 0;
	if (!cmd->argv[1])
	{
		print_env_lst_export(env_lst);
		return (0);
	}
	i = 1;
	while (cmd->argv[i])
	{
		update_env(cmd->argv[i], env_lst);
		i++;
	}
	return (0);
}
