#include "main.h"

int quotes_token_mal(t_token **tokens, char *str, int *i, size_t *len)
{
	t_token	*token;
	char	quote;
	const char delimiter[7] = "|<> \n\t\0";
	
	quote = str[*i];
	(*len)++;
	(*i)++;
	while (str[*i] != quote && str[*i] != '\0')
	{
		(*len)++;
		(*i)++;
	}
	(*len)++;
	(*i)++;
	// if (ft_strchr(delimiter, str[*i]) || !str[*i])
	if (*len)
	{
		token = token_new(str, *i, *len, NO_TAG, quote);
		if (!token)
			return (1);
		token_add_back(tokens, token);
		(*len) = 0;
	}
	return (0);
}

int delimiter_token_mal(t_token **tokens, char *str, int *i, size_t *len)
{
	t_token	*token;
	tags	tag;
	const char delimiter[7] = "|<> \n\t\0";
	const char tags[4] = "|<>\0";
	
	tag = NO_TAG;
	while (ft_strchr(delimiter, str[*i]) && str[*i])
	{
		if (ft_strchr(tags, str[*i]))
			tag = NEED_DECIDE;
		(*i)++;
		(*len)++;
	}
	if (*len)
	{
		token = token_new(str, *i, *len, tag, NO_QUOTE);
		if (!token)
			return (1);
		token_add_back(tokens, token);
		(*len) = 0;
	}
	return (0);
}

int token_mal(t_token **tokens, char *str, int *i, size_t *len)
{
	t_token	*token;
	const char delimiter[7] = "|<> \n\t\0";
	const char quotes[3] = "\'\"\0";

	while (!ft_strchr(delimiter, str[*i]) && !ft_strchr(quotes, str[*i]) && \
	 str[*i])
	{
		(*i)++;
		(*len)++;
	}
	if (*len)
	{
		token = token_new(str, *i, *len, NO_TAG, NO_QUOTE);
		if (!token)
			return (1);
		token_add_back(tokens, token);
		(*len) = 0;
	}
	return (0);
}

t_token	*token_last(t_token *lst)
{
	t_token	*temp_lst;

	temp_lst = lst;
	if (temp_lst)
	{
		while (temp_lst->next != 0)
			temp_lst = temp_lst->next;
	}
	return (temp_lst);
}

int lexical_analyzer(t_token **tokens, char *str, t_env **env_lst)
{
	int	i;
	const char delimiter[7] = "|<> \n\t\0";
	const char quotes[3] = "\'\"\0";
	size_t len;

	*tokens = 0;
	i = 0;
	len = 0;
	while (str[i] != 0)
	{
		// FIXME: echo'h'
		if (ft_strchr(quotes, str[i]) && quotes_token_mal(tokens, str, &i, &len))
			return (1);
		if (ft_strchr(delimiter, str[i]) && delimiter_token_mal(tokens, str, &i, &len))
			return (1);
		if (!ft_strchr(delimiter, str[i]) && !ft_strchr(quotes, str[i]) && \
		token_mal(tokens, str, &i, &len))
			return (1);
	}
	if (update_tokens(tokens, env_lst))
		return (1);
	return (0);
}