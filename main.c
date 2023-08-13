/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gichlee <gichlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 21:16:36 by gichlee           #+#    #+#             */
/*   Updated: 2023/08/13 15:07:16 by gichlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	init_cmds_info(char *input, t_cmd **cmds, t_info **info)
{
	if (!(*input))
		return (0);
	add_history(input);
	*cmds = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
	if (!(*cmds))
		return (0);
	*info = (t_info *)ft_calloc(1, sizeof(t_info));
	if (!(*info))
	{
		free(*cmds);
		return (0);
	}
	return (1);
}

int	loop_prompt(t_env **env_lst)
{
	char	*input;
	t_cmd	*cmds;
	t_info	*info;

	while (1)
	{
		update_exit_status(env_lst, g_exit_status);
		input = readline("minishell $ ");
		if (!input)
			return (null_input_exit());
		if (init_cmds_info(input, &cmds, &info))
		{
			if (parsing(input, &cmds, env_lst, info))
				continue ;
			g_exit_status = execute(cmds, env_lst, info);
			if (is_exit_status(env_lst, &g_exit_status))
				break ;
		}
		free(input);
	}
	return (g_exit_status % 256);
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*env_lst;

	(void)argv;
	if (argc != 1)
		return (1);
	if (set_terminal())
		return (1);
	set_signal();
	if (envp_to_env_lst(envp, &env_lst))
	{
		env_lstclear(&env_lst, &free);
		return (1);
	}
	if (loop_prompt(&env_lst))
	{
		env_lstclear(&env_lst, &free);
		return (g_exit_status % 256);
	}
	env_lstclear(&env_lst, &free);
	return (g_exit_status % 256);
}
