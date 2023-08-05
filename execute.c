/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gichlee <gichlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 21:59:38 by gichlee           #+#    #+#             */
/*   Updated: 2023/08/05 13:57:03 by gichlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	execute(t_cmd *cmds, t_env **env_lst)
{
	if (cmds->built_in)
		run_built_in(cmds, env_lst);
	pipex(cmds, env_lst);
	cmds_clear(&cmds, free);
	return (0);
}