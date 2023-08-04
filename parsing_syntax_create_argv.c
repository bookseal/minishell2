#include "main.h"

void	test_cmd_argv_print(t_cmd *cmd)
{
	int	i = 0;
	while (cmd->argv[i])
	{
		printf("argv[i] = %s\n", cmd->argv[i]);
		i++;
	}
}

int	get_argc(t_token *tokens)
{
	int		argc;

	argc = 0;
	while (tokens != 0 && tokens->tag != PIPE)
	{
		if (tokens->tag) // If tmp is a redirection
		{
			// 다른 곳에서 redirect_info로 다룸
			// tmp = tmp->next; // Skip the redirection token
			// if (tmp != 0 && !tmp->tag) // If the next token is a word
			// 	tmp->tag = ; // Change the type to variable
		}
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
	t_token	*prev;

	i = 0;
	tmp = *tokens;
	// prev = *tokens;
	while (tmp != 0 && tmp->tag != PIPE)
	{
		if (!tmp->tag)
		{
			cmd->argv[i] = ft_strdup(tmp->value);
			// FIXME: replace need to del
			tmp->need_to_del = true;
			tmp = tmp->next;
			// arg_del_next(tokens, &tmp, &prev);
			i++;
		}
		else
		{
			// prev = tmp;
			tmp = tmp->next;
		}
	}
	unnecessary_token_delete(tokens);
}

int create_argv(t_cmd *cmd, t_token **tokens)
{
	cmd->argv = (char **)ft_calloc(get_argc(*tokens) + 1, sizeof(char *));
	if (!cmd->argv)
		return (1);
	tokens_to_argv(cmd, tokens);
	// test_cmd_argv_print(cmd);
	return (0);
}