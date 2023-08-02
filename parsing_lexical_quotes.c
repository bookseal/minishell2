#include "main.h"

int	is_valid_quote_token(t_token *tokens)
{
	int i;
	char start_quote_lo;
	t_token	*token;

	token = tokens;
	while (token)
	{
		i = 0;
		start_quote_lo = token->value[i];
		if (start_quote_lo != '\'' && start_quote_lo != '\"')
			return (0);
		while (token->value[++i])
		{
			if (token->value[i] == start_quote_lo && token->value[i + 1] != '\0')
				return (0);
		}
		if (token->value[i - 1] != start_quote_lo)
			return (0);
		token = token->next;
	}
	return (1);
}

static void handle_quote_lo(t_token *tokens, int *i, char c)
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
				handle_quote_lo(tokens, &i, '\'');
			else if (tokens->value[i] == '\"')
				handle_quote_lo(tokens, &i, '\"');
			else
				tokens->quote_lo[i] = '0';
		}
	}
	return (0);
}

void remove_char_at_index(t_token *tokens, int index) {
	char	*new_value;
	char	*new_quote_lo;

	tokens->value[index] = '\0';
	tokens->quote_lo[index] = '\0';
	new_value = ft_strjoin(tokens->value, tokens->value + index + 1);
	new_quote_lo = ft_strjoin(tokens->quote_lo, tokens->quote_lo + index + 1);
	free(tokens->value);
	free(tokens->quote_lo);
	tokens->value = new_value;
	tokens->quote_lo = new_quote_lo;
}

void remove_quotes(t_token *tokens)
{
	int		i;
	char	c;

	i = 0;
	c = tokens->value[i];
	while (c)
	{
		c = tokens->value[i];
		if ((c == '\'' || c == '\"') && tokens->quote_lo[i] == '1')
		{
			remove_char_at_index(tokens, i);
			i--;
			// if (tokens->tag == 'h')
			// 	tokens->tag = 'H';
		}
		i++;
	}
}
