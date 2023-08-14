/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_clear.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gichlee <gichlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 15:01:32 by gichlee           #+#    #+#             */
/*   Updated: 2023/08/14 19:12:11 by gichlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	info_cmds_input_clear(t_cmd *cmds, t_info *info, char *input)
{
	int	i;

	i = 0;
	if (info)
	{
		while (info->fd && info->fd[i])
		{
			free(info->fd[i]);
			i++;
		}
		free(info);
		if (info->fd)
			free(info->fd);
	}
	cmds_clear(&cmds, &free);
	free(input);
	return (g_exit_status % 256);
}
