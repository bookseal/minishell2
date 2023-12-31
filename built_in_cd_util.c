/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cd_util.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwonle2 <jiwonle2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 19:46:28 by jiwonle2          #+#    #+#             */
/*   Updated: 2023/08/14 18:57:56 by jiwonle2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	new_env_util(t_env **env, char *key, char *value, t_env_tag tag)
{
	while (*env)
	{
		if (!ft_strncmp((*env)->key, key, ft_strlen((*env)->key) + 1))
		{
			free((*env)->value);
			(*env)->value = ft_strdup(value);
			(*env)->tag = tag;
			break ;
		}
		(*env) = (*env)->next;
	}
}

char	*get_pwd(t_env **env_lst)
{
	t_env	*env;

	env = *env_lst;
	while (env)
	{
		if (!ft_strncmp(env->key, "PWD", 4))
			return (ft_strdup(env->value));
		env = env->next;
	}
	return (0);
}

void	update_pwds(char *oldpwd, t_env *env)
{
	while (env != 0)
	{
		if (ft_strncmp(env->key, "PWD", 4) == 0)
		{
			free(env->value);
			env->value = getcwd(NULL, 0);
		}
		else if (ft_strncmp(env->key, "oldpwd", 7) == 0)
		{
			if (env->value)
				free(env->value);
			if (oldpwd)
				env->value = ft_strdup(oldpwd);
			else
				env->value = ft_strdup("");
		}
		env = env->next;
	}
}

static int	cd_parent(char *path, t_env **env_lst, char *oldpwd)
{
	int		exit_status;

	wait(&exit_status);
	if (WIFEXITED(exit_status))
		exit_status = WEXITSTATUS(exit_status);
	if (exit_status == 0 && chdir(path) == 0)
	{
		update_pwds(oldpwd, *env_lst);
		free(path);
		return (0);
	}
	if (exit_status != 0)
		print_error(0, "cd: error ");
	else
		perror(path);
	free(path);
	if (oldpwd)
		free(oldpwd);
	return (1);
}

int	go_to_path(char *path, t_env **env_lst)
{
	char	*oldpwd;
	int		pid;

	oldpwd = get_pwd(env_lst);
	pid = fork();
	if (pid == 0)
	{
		if (!chdir(path) && !getcwd(NULL, 0))
			exit(1);
		exit(0);
	}
	else
		return (cd_parent(path, env_lst, oldpwd));
}
