/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gichlee <gichlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 21:59:38 by gichlee           #+#    #+#             */
/*   Updated: 2023/08/14 15:09:10 by gichlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	execute(t_cmd *cmds, t_env **env_lst, t_info *info)
{
	pipex(cmds, env_lst, info);
	return (g_exit_status);
}
