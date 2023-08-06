/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_lexical_divide_delimiters.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gichlee <gichlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 21:55:27 by gichlee           #+#    #+#             */
/*   Updated: 2023/08/06 21:36:35 by gichlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	strs_to_tokens(t_token **token, char **strs)
{
	int	i;
	t_token *new_tokens;
	t_token	*new;
	t_token *temp;

	new_tokens = 0;
	i = 0;
	while (strs[i])
	{
		new = token_new(strs[i], 0, ft_strlen(strs[i]),\
		 (*token)->need_to_del, (*token)->quote);
		if (!new)
		{
			token_clear(&new_tokens, &free);
			return (1);
		}
		token_add_back(&new_tokens, new);
		i++;
	}
	temp = (*token)->next;
	token_add_back(&new_tokens, temp);
	(*token)->next = new_tokens;
	return (0);
}

int divide_delimiters(t_token **tokens)
{
	char	**strs;
	t_token	*token;

	token = *tokens;
	while (token)
	{
		if (!token->need_to_del && token->tag == NEED_DECIDE && ft_strchr(token->value, ' '))
		{
			token->need_to_del = TRUE;
			strs = ft_split(token->value, ' ');
			if (!strs)
				return (1);
			if (strs_to_tokens(&token, strs))
				return (1);
			free(strs);
		}
		token = token->next;
	}
	return (0);
}