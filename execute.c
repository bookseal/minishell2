/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gichlee <gichlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 21:59:38 by gichlee           #+#    #+#             */
/*   Updated: 2023/08/12 16:47:42 by gichlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	execute(t_cmd *cmds, t_env **env_lst, t_info *info)
{
	// pipex_gichlee(cmds, env_lst);
	pipex(cmds, env_lst, info);
	cmds_clear(&cmds, free);
	// printf("execute g = %d\n", g_exit_status);
	return (g_exit_status);
}