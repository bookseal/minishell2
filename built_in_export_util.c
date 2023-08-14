/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_export_util.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gichlee <gichlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 19:32:52 by jiwonle2          #+#    #+#             */
/*   Updated: 2023/08/14 19:41:02 by gichlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*env_dup(t_env *head)
{
	t_env	*new_head;
	t_env	*tail;
	t_env	*temp;

	new_head = NULL;
	tail = NULL;
	if (head == NULL)
		return (NULL);
	while (head)
	{
		temp = env_lstnew_malloc(head->key, head->value);
		temp->tag = head->tag;
		if (new_head == NULL)
		{
			new_head = temp;
			tail = temp;
		}
		else
		{
			tail->next = temp;
			tail = temp;
		}
		head = head->next;
	}
	return (new_head);
}
