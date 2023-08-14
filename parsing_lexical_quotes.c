/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_lexical_quotes.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gichlee <gichlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 21:52:22 by gichlee           #+#    #+#             */
/*   Updated: 2023/08/14 20:13:04 by gichlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_quote_lo(t_token *tokens, int *i, char c)
{
	char	v;

	tokens->quote_lo[*i] = '1';
	(*i)++;
	v = tokens->value[*i];
	while (v && v != c)
	{
		tokens->quote_lo[*i] = '0';
		(*i)++;
		v = tokens->value[*i];
	}
	tokens->quote_lo[*i] = '1';
}

int	insert_quotes_location(t_token *tokens)
{
	int	i;

	while (tokens)
	{
		i = 0;
		while (i < (int)ft_strlen(tokens->value))
		{
			if (tokens->value[i] == '\'')
				handle_quote_lo(tokens, &i, '\'');
			else if (tokens->value[i] == '\"')
				handle_quote_lo(tokens, &i, '\"');
			else
				tokens->quote_lo[i] = '0';
			i++;
		}
		tokens = tokens->next;
	}
	return (0);
}

void	remove_char_at_index(t_token *tokens, int index)
{
	char	*new_value;
	char	*new_quote_lo;

	tokens->value[index] = '\0';
	tokens->quote_lo[index] = '\0';
	new_value = ft_strjoin(tokens->value, tokens->value + index + 1);
	new_quote_lo = ft_strjoin(tokens->quote_lo, tokens->quote_lo + index + 1);
	free(tokens->value);
	free(tokens->quote_lo);
	tokens->value = new_value;
	tokens->quote_lo = new_quote_lo;
}

void	remove_quotes(t_token *tokens)
{
	int		i;
	char	c;

	while (tokens)
	{
		i = 0;
		c = tokens->value[i];
		while (c)
		{
			c = tokens->value[i];
			if ((c == '\'' || c == '\"') && tokens->quote_lo[i] == '1')
			{
				remove_char_at_index(tokens, i);
				i--;
			}
			i++;
		}
		tokens = tokens->next;
	}
}
