#include "main.h"

void	value_trim(t_token *token)
{
	char *new_value;

	while (token)
	{
		new_value = ft_strtrim(token->value, " ");
		free(token->value);
		token->value = new_value;
		token = token->next;
	}
}

int	update_tags(t_token **tokens)
{
	if (divide_delimiters(tokens))
		return (1);
	if (assign_tags(tokens))
		return (1);
	return (0);
}

void	unnecessary_token_delete(t_token **tokens)
{
	t_token *token;
	t_token *tmp;
	t_token *prev;
	
	token = *tokens;
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
	if (update_tags(tokens))
		return (1);
	unnecessary_token_delete(tokens);
	if (!is_valid_quote_token(*tokens))
	{
		token_clear(tokens, &free);
		return (1);
	}
	insert_quotes_location(*tokens);
	replace_env(*tokens, *env_lst);
	remove_quotes(*tokens);
	return (0);
}