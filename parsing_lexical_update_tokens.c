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
	// TODO: assign_tags
	
	return (0);
}

int	update_tokens(t_token **tokens, t_env **env_lst)
{
	value_trim(*tokens);
	update_tags(tokens);
	// TODO: token_delete
	// TODO: update_quotes(tokens)
	// TODO: update_env(tokens, env_lst)
	return (0);
}