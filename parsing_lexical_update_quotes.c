#include "main.h"

int	is_valid_token(char *token)
{
	int i;
	char start_quote;

	i = 0;
	start_quote = token[i];
	if (start_quote != '\'' && start_quote != '\"')
		return (0);
	while (token[++i])
	{
		if (token[i] == start_quote && token[i + 1] != '\0')
			return (0);
	}
	if (token[i - 1] != start_quote)
		return (0);
	return (1);
}

int update_quotes(t_token **tokens)
{
	if (!is_valid_token(*tokens))
	{
		token_clear(&tokens, &free);
		return (1);
	}
	// TODO: remove quotes()
	return (0);
}