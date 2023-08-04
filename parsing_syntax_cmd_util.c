/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_syntax_cmd_util.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gichlee <gichlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 22:11:14 by gichlee           #+#    #+#             */
/*   Updated: 2023/08/04 22:17:24 by gichlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	cmd_delone(t_cmd *cmd, void (*del)(void *))
{
	if (cmd == 0 || del == 0)
		return ;
	
	strs_free(cmd->argv);
	free(cmd);
}

void	cmds_clear(t_cmd **cmds, void (*del)(void *))
{
	t_cmd	*next_cmd;

	if (*cmds == 0 || del == 0)
		return ;
	while (*cmds != 0)
	{
		next_cmd = (*cmds)->next;
		cmd_delone(*cmds, del);
		*cmds = next_cmd;
	}
}
