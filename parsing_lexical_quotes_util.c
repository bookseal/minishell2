/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_lexical_quotes_util.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gichlee <gichlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 15:58:56 by gichlee           #+#    #+#             */
/*   Updated: 2023/08/13 19:59:15 by gichlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	calculate_count_c(t_token *token, char c, int *count_c, int *i)
{
	(*i)++;
	while (token->value[++(*i)])
	{
		if (token->value[*i] == c && token->value[*i + 1] != '\0')
			(*count_c)++;
	}
}

int	is_valid_quote_token(t_token **tokens)
{
	int		i;
	char	c;
	int		count_c;
	t_token	*token;

	token = *tokens;
	while (token)
	{
		if (!token->quote)
		{
			token = token->next;
			continue ;
		}
		i = 0;
		c = token->value[i];
		count_c = 1;
		if (!token->value[i + 1])
			return (0);
		calculate_count_c(token, c, &count_c, &i);
		if (count_c % 2 != 0)
			return (0);
		token = token->next;
	}
	return (1);
}
