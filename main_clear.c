/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_clear.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gichlee <gichlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 15:01:32 by gichlee           #+#    #+#             */
/*   Updated: 2023/08/14 16:43:30 by gichlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	info_cmds_input_clear(t_cmd *cmds, t_info *info, char *input)
{
	int	i;

	i = 0;
	while (info->fd[i])
	{
		free(info->fd[i]);
		i++;
	}
	free(info->fd);
	free(info);
	cmds_clear(&cmds, &free);
	free(input);
	return (g_exit_status % 256);
}
