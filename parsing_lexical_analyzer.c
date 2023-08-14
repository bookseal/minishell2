/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_lexical_analyzer.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gichlee <gichlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 21:47:54 by gichlee           #+#    #+#             */
/*   Updated: 2023/08/14 13:45:08 by gichlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	store_token(t_token **tokens, int *token_count, size_t *len, char *seg)
{
	const char	special_chars[7] = "<>| \t\n\0";
	t_token		*token;
	char		*token_value;
	t_quotes	quote;

	if (seg && *len)
	{
		quote = NO_QUOTE;
		token_value = (char *)malloc(sizeof(char) * (*len + 1));
		ft_strlcpy(token_value, seg, *len + 1);
		if (token_value[0] == '\'')
			quote = SINGLE;
		else if (token_value[0] == '\"')
			quote = DOUBLE;
		if (ft_strchr(special_chars, token_value[0]))
			token = token_new(token_value, NEED_DECIDE, quote);
		else
			token = token_new(token_value, NO_TAG, quote);
		token_add_back(tokens, token);
		(*token_count)++;
		*len = 0;
	}
}

static char	*parse_single_quotes(char *input, int *index, size_t *len)
{
	const char	special_chars[7] = "<>| \t\n\0";

	if (input[*index] == '\'')
	{
		(*len)++;
		(*index)++;
		while (input[*index] && input[*index] != '\'')
		{
			(*len)++;
			(*index)++;
		}
		(*len)++;
		(*index)++;
		if (!input[*index] || ft_strchr(special_chars, input[*index]))
			return (input + *index - *len);
	}
	return (0);
}

static char	*parse_double_quotes(char *input, int *index, size_t *len)
{
	const char	special_chars[7] = "<>| \t\n\0";

	if (input[*index] == '\"')
	{
		(*len)++;
		(*index)++;
		while (input[*index] && input[*index] != '\"')
		{
			(*len)++;
			(*index)++;
		}
		(*len)++;
		(*index)++;
		if (!input[*index] || ft_strchr(special_chars, input[*index]))
			return (input + *index - *len);
	}
	return (0);
}

static char	*parse_word_or_operator(char *input, int *index, size_t *len)
{
	const char	special_chars[7] = "<>| \t\n\0";

	if (ft_strchr(special_chars, input[*index]) && input[*index])
	{
		while (ft_strchr(special_chars, input[*index]) && input[*index])
		{
			(*len)++;
			(*index)++;
		}
		return (input + *index - *len);
	}
	else if (input[*index] && input[*index] != '\'' && input[*index] != '\"')
	{
		while (!ft_strchr(special_chars, input[*index]) && input[*index] && \
			input[*index] != '\'' && input[*index] != '\"')
		{
			(*len)++;
			(*index)++;
		}
		if (!input[*index] || (input[*index] != '\'' && input[*index] != '\"'))
			return (input + *index - *len);
	}
	return (0);
}

int	lexical_analyzer(t_token **tokens, char *input, t_env **env_lst)
{
	int		pos;
	int		token_count;
	size_t	len;
	char	*segment_start;

	pos = 0;
	token_count = 0;
	len = 0;
	while (input[pos])
	{
		segment_start = parse_single_quotes(input, &pos, &len);
		store_token(tokens, &token_count, &len, segment_start);
		segment_start = parse_double_quotes(input, &pos, &len);
		store_token(tokens, &token_count, &len, segment_start);
		segment_start = parse_word_or_operator(input, &pos, &len);
		store_token(tokens, &token_count, &len, segment_start);
	}
	update_tokens(tokens, env_lst);
	return (0);
}
