#include "main.h"

int	is_valid_quote_token(t_token **tokens)
{
	int i;
	char c;
	t_token	*token;

	token = *tokens;
	while (token)
	{
		if (!token->quote)
		{
			token = token->next;
			continue ;
		}
		i = 0;
		c = token->value[i];
		if (c != '\'' && c != '\"')
			return (0);
		while (token->value[++i])
		{
			if (token->value[i] == c && token->value[i + 1] != '\0')
				return (0);
		}
		if (token->value[i - 1] != c)
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

	while (tokens)
	{
		if (tokens->quote)
		{
			i  = 0;
			while (tokens->value[i] != '\0')
			{
				if (tokens->value[i] == '\'')
					handle_quote_lo(tokens, &i, '\'');
				else if (tokens->value[i] == '\"')
					handle_quote_lo(tokens, &i, '\"');
				else
					tokens->quote_lo[i] = '0';
				i++;
			}
		}
		tokens = tokens->next;
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

	while (tokens)
	{
		i = 0;
		c = tokens->value[i];
		while (c)
		{
			c = tokens->value[i];
			if ((c == '\'' || c == '\"') && tokens->quote_lo[i] == '1')
			{
				remove_char_at_index(tokens, i);
				i--;
			}
			i++;
		}
		tokens = tokens->next;
	}
}
