/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_env_replace.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gichlee <gichlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 21:54:08 by gichlee           #+#    #+#             */
/*   Updated: 2023/08/12 21:56:26 by gichlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	dollar_to_env(t_token *token, int *start_i, t_env *env_lst)
{
	char	*value_substr;
	int		len_envkey;
	t_env	*env;

	len_envkey = get_len_envkey(token, *start_i);
	if (!len_envkey)
		return (1);
	value_substr = ft_substr(token->value, *start_i + 1, len_envkey);
	env = get_env_value(value_substr, env_lst);
	if (!env)
	{
		remove_dollar_word(token, start_i, value_substr);
		return (1);
	}
	if (value_substr_to_env_value(token, *start_i, env, len_envkey))
		return (1);
	return (0);
}

int	handle_dou_q(t_token *token, t_env *env_lst, int *i)
{
	(*i)++;
	while (*i < ft_strlen(token->value) && token->value[*i] != '\"')
	{
		if (token->value[*i] == '$' && dollar_to_env(token, i, env_lst))
			return (1);
		(*i)++;
	}
	return (0);
}

int	handle_single_quote(t_token *token, int *i)
{
	(*i)++;
	while (*i < ft_strlen(token->value) && token->value[*i] != '\'')
		(*i)++;
	return (0);
}

void	replace_env(t_token *tokens, t_env *env_lst)
{
	int		start_i;
	char	c;
	char	front;

	while (tokens)
	{	
		start_i = 0;
		c = tokens->value[start_i];
		front = c;
		while (c)
		{
			c = tokens->value[start_i];
			if (front == '\'' && handle_single_quote(tokens, &start_i))
				;
			else if (front == '\"' && handle_dou_q(tokens, env_lst, &start_i))
				;
			else if (c == '$' && dollar_to_env(tokens, &start_i, env_lst))
				start_i--;
			start_i++;
		}
		tokens = tokens->next;
	}
}
