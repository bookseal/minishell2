/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_lexical_divide_delimiters.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gichlee <gichlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 21:55:27 by gichlee           #+#    #+#             */
/*   Updated: 2023/08/12 22:28:09 by gichlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	divide_delimiters(t_token **tokens)
{
	char	**strs;
	t_token	*token;

	token = *tokens;
	while (token)
	{
		if (!token->need_to_del && token->tag == NEED_DECIDE && \
		ft_strchr(token->value, ' '))
		{
			token->need_to_del = TRUE;
			strs = ft_split(token->value, ' ');
			if (!strs)
				return (1);
			free(strs);
		}
		token = token->next;
	}
	return (0);
}
