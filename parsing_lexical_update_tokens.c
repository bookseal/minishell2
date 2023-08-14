/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_lexical_update_tokens.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gichlee <gichlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 21:50:45 by gichlee           #+#    #+#             */
/*   Updated: 2023/08/14 20:09:33 by gichlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	value_trim(t_token *token)
{
	char	*new_value;

	while (token)
	{
		new_value = ft_strtrim(token->value, " ");
		free(token->value);
		token->value = new_value;
		token = token->next;
	}
}

void	unnecessary_token_delete(t_token **tokens)
{
	t_token	*token;
	t_token	*tmp;
	t_token	*prev;

	token = *tokens;
	prev = 0;
	while (token)
	{
		tmp = token->next;
		if (token->need_to_del || !ft_strlen(token->value))
		{
			if (prev != NULL)
				prev->next = tmp;
			else
				*tokens = tmp;
			token_delone(token, &free);
		}
		else
			prev = token;
		token = tmp;
	}
}

int	update_tokens(t_token **tokens, t_env **env_lst)
{
	value_trim(*tokens);
	if (assign_tags(tokens))
		return (1);
	unnecessary_token_delete(tokens);
	if (!is_valid_quote_token(tokens))
	{
		token_clear(tokens, &free);
		print_error(0, "not matched quotes");
		return (update_exit_status(env_lst, 1));
	}
	replace_env(*tokens, *env_lst);
	insert_quotes_location(*tokens);
	remove_quotes(*tokens);
	return (0);
}
