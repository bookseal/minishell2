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

int	envp_to_env_lst(char **envp, t_env **env_lst)
{
	char	*equal_ptr;
	int		i;
	t_env	*env_node;

	*env_lst = 0;
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
