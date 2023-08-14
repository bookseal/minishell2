/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_clear.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gichlee <gichlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 15:01:32 by gichlee           #+#    #+#             */
/*   Updated: 2023/08/14 15:05:38 by gichlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	info_cmds_input_clear(t_cmd *cmds, t_info *info, char *input)
{
	free(info->fd);
	free(info);
	cmds_clear(&cmds, &free);
	free(input);
}
