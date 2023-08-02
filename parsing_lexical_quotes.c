#include "main.h"

int	is_valid_quote_token(t_token *tokens)
{
	int i;
	char start_quote;
	t_token	*token;

	token = tokens;
	while (token)
	{
		i = 0;
		start_quote = token->value[i];
		if (start_quote != '\'' && start_quote != '\"')
			return (0);
		while (token->value[++i])
		{
			if (token->value[i] == start_quote && token->value[i + 1] != '\0')
				return (0);
		}
		if (token->value[i - 1] != start_quote)
			return (0);
		token = token->next;
	}
	return (1);
}

static void handle_quotes(t_token *tokens, int *i, char c)
{
	tokens->quote_lo[*i] = '1';
	while (tokens->value[++(*i)] != c)
		tokens->quote_lo[*i] = '0';
	tokens->quote_lo[*i] = '1';
}

int insert_quotes_location(t_token *tokens)
{
	int	i;

	i  = -1;
	if (tokens != 0)
	{
		while (tokens->value[++i] != '\0')
		{
			if (tokens->value[i] == '\'')
				handle_quotes(tokens, &i, '\'');
			else if (tokens->value[i] == '\"')
				handle_quotes(tokens, &i, '\"');
			else
				tokens->quote_lo[i] = '0';
		}
	}
	return (0);
}