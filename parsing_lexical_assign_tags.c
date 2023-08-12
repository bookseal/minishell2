/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_lexical_assign_tags.C                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gichlee <gichlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 21:51:56 by gichlee           #+#    #+#             */
/*   Updated: 2023/08/12 22:29:21 by gichlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	iterate_tags(t_token *token)
{
	char	*str;

	str = token->value;
	if (*str == '\0')
	{
		token->need_to_del = TRUE;
		return (0);
	}
	if (!ft_strncmp(str, "|", 2))
		token->tag = PIPE;
	else if (!ft_strncmp(str, "<", 2))
		token->tag = REDIRECT_IN;
	else if (!ft_strncmp(str, ">", 2))
		token->tag = REDIRECT_OUT;
	else if (!ft_strncmp(str, "<<", 3))
		token->tag = HEREDOC;
	else if (!ft_strncmp(str, ">>", 3))
		token->tag = APPEND_OUT;
	else
		return (1);
	if (token->tag > 1)
	{
		if (!token->next)
			return (1);
		token->next->tag = REDIRECT_INFO;
	}
	return (0);
}

int	assign_tags(t_token **tokens)
{
	t_token	*token;

	token = *tokens;
	while (token)
	{
		if (token->tag == NEED_DECIDE && iterate_tags(token))
			return (print_error(token, "token"));
		token = token->next;
	}
	return (0);
}
