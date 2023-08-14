/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_syntax_create_argv.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gichlee <gichlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 22:20:19 by gichlee           #+#    #+#             */
/*   Updated: 2023/08/14 19:12:11 by gichlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_argc(t_token *tokens)
{
	int		argc;

	argc = 0;
	while (tokens != 0 && tokens->tag != PIPE)
	{
		if (tokens->tag)
			;
		else
			argc++;
		tokens = tokens->next;
	}
	return (argc);
}

void	arg_del_next(t_token **tokens, t_token **tmp, t_token **prev)
{
	if (*tokens == *tmp)
	{
		*tokens = (*tmp)->next;
		token_delone(*tmp, &free);
		*tmp = *tokens;
	}
	else
	{
		(*prev)->next = (*prev)->next;
		token_delone(*prev, &free);
		*tmp = (*prev)->next;
	}
}

void	tokens_to_argv(t_cmd *cmd, t_token **tokens)
{
	int		i;
	t_token	*tmp;

	i = 0;
	tmp = *tokens;
	while (tmp != 0 && tmp->tag != PIPE)
	{
		if (!tmp->tag)
		{
			cmd->argv[i] = ft_strdup(tmp->value);
			tmp->need_to_del = TRUE;
			tmp = tmp->next;
			i++;
		}
		else
			tmp = tmp->next;
	}
	unnecessary_token_delete(tokens);
}

int	create_argv(t_cmd *cmd, t_token **tokens)
{
	cmd->argv = (char **)ft_calloc(get_argc(*tokens) + 1, sizeof(char *));
	if (!cmd->argv)
		return (1);
	tokens_to_argv(cmd, tokens);
	return (0);
}
