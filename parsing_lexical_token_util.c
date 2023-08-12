/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_lexical_token_util.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gichlee <gichlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 21:53:21 by gichlee           #+#    #+#             */
/*   Updated: 2023/08/12 21:53:26 by gichlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	token_delone(t_token *lst, void (*del)(void *))
{
	if (lst == 0 || del == 0)
		return ;
	del(lst->value);
	del(lst->quote_lo);
	free(lst);
}

void	token_clear(t_token **lst, void (*del)(void *))
{
	t_token	*next_lst;

	if (*lst == 0 || del == 0)
		return ;
	while (*lst != 0)
	{
		next_lst = (*lst)->next;
		token_delone(*lst, del);
		*lst = next_lst;
	}	
}

void	token_add_back(t_token **lst, t_token *new)
{
	t_token	*head;
	t_token	*temp_lst;

	head = *lst;
	if (head == 0)
		*lst = new;
	else
	{
		temp_lst = head;
		while (temp_lst->next != 0)
			temp_lst = temp_lst->next;
		temp_lst->next = new;
	}
}

t_token	*token_new(char *value, t_tags tag, char quote)
{
	t_token	*token;

	token = (t_token *)ft_calloc(1, sizeof(t_token));
	if (!token)
		return (0);
	token->value = value;
	token->tag = tag;
	if (quote == '\'')
		token->quote = SINGLE;
	else if (quote == '\"')
		token->quote = DOUBLE;
	else
		token->quote = NO_QUOTE;
	token->quote_lo = (char *)ft_calloc(ft_strlen(token->value), sizeof(char));
	return (token);
}

t_token	*token_new_2(char *str, int i, size_t len, t_tags tag, char quote)
{
	t_token	*token;
	size_t	start;

	token = (t_token *)ft_calloc(1, sizeof(t_token));
	if (token == 0)
		return (0);
	if (i < len)
		start = 0;
	else
		start = i - len;
	token->value = ft_substr(str, start, len);
	token->tag = tag;
	if (quote == '\'')
		token->quote = SINGLE;
	else if (quote == '\"')
		token->quote = DOUBLE;
	else
		token->quote = NO_QUOTE;
	token->quote_lo = (char *)ft_calloc(ft_strlen(token->value), sizeof(char));
	token->next = 0;
	return (token);
}
