/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gichlee <gichlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 21:16:36 by gichlee           #+#    #+#             */
/*   Updated: 2023/08/14 19:19:56 by gichlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	readline_to_input(char **input)
{
	*input = readline("minishell $ ");
	if (!(*input))
		return (null_input_exit());
	return (0);
}

int	loop_prompt(t_env **env_lst)
{
	char	*input;
	t_cmd	*cmds;
	t_info	*info;
	int		error;

	info = 0;
	while (1)
	{
		update_exit_status(env_lst, g_exit_status);
		if (readline_to_input(&input))
			return (1);
		error = parsing(input, &cmds, env_lst, &info);
		if (error)
		{
			info_cmds_input_clear(cmds, info, input);
			if (error == 4)
				break ;
			continue ;
		}
		g_exit_status = execute(cmds, env_lst, info);
		if (is_exit_status(env_lst, &g_exit_status))
			return (info_cmds_input_clear(cmds, info, input));
		info_cmds_input_clear(cmds, info, input);
	}
	return (info_cmds_input_clear(cmds, info, input));
}

void	leak(void)
{
	system("leaks $PPID");
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*env_lst;

	atexit(leak);
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
	loop_prompt(&env_lst);
	env_lstclear(&env_lst, &free);
	return (g_exit_status % 256);
}
