/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   main_envp_to_env_lst.c							 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: gichlee <gichlee@student.42.fr>			+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2023/08/04 21:46:19 by gichlee		   #+#	#+#			 */
/*   Updated: 2023/08/04 21:48:31 by gichlee		  ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "main.h"

// int update_level_up(int level, t_env *env)
// {
// 	char	*level_str;

// 	if (level < MIN_LEVEL)
// 		level = MIN_LEVEL;
// 	else if (level <= MAX_LEVEL)
// 		level++;
// 	else
// 		level = MIN_LEVEL;
// 	level_str = ft_itoa(level);
// 	if (!level_str)
// 		return (1);
// 	free(env->value);
// 	env->value = level_str;
// 	// printf("level = %d\n", level);
// 	return (0);
// }

// int update_shell_level(t_env **env_lst)
// {
// 	t_env	*env;
// 	int		level;

// 	env = *env_lst;
// 	while (env)
// 	{
// 		if (!strncmp(env->key, "SHLVL", strlen(env->key)))
// 		{
// 			level = ft_atoi(env->value);
// 			if (!level)
// 				level = 1;
// 			return (update_level_up(level, env));
// 		}
// 		env = env->next;
// 	}
// 	if (!env)
// 	{
// 		env = env_lstnew_malloc("SHLVL", "1");
// 		env_lstadd_back(env_lst, env);
// 	}
// 	return (0);
// }

int envp_to_env_lst(char **envp, t_env **env_lst)
{
	char	*equal_ptr;
	int		i;
	t_env	*env_node;

	i = 0;
	while (envp[i])
	{
		equal_ptr = ft_strchr(envp[i], '=');
		*equal_ptr = '\0';
		env_node = env_lstnew_malloc(envp[i], equal_ptr + 1);
		if (!env_node)
			return (1);
		env_lstadd_back(env_lst, env_node);
		i++;
	}
	return (0);
}