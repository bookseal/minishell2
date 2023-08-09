#include "main.h"

static void	store_token(t_token **tokens, int *token_count, size_t *length, char *segment)
{
	const char special_chars[7] = "<>| \t\n\0";
	t_token	*token;
	char	*token_value;

	if (segment && *length)
	{
		token_value = (char *)malloc(sizeof(char) * (*length + 1));
		ft_strlcpy(token_value, segment, *length + 1);
		if (ft_strchr(special_chars, token_value[0]))
			token = token_new(token_value, NEED_DECIDE, 0);
		else
			token = token_new(token_value, NO_TAG, 0);
		token_add_back(tokens, token);
		(*token_count)++;
		// segment = NULL;
		*length = 0;
	}
}

static char	*parse_single_quotes(char *input, int *index, size_t *length)
{
	const char special_chars[7] = "<>| \t\n\0";
	if (input[*index] == '\'')
	{
		(*length)++;
		(*index)++;
		while (input[*index] && input[*index] != '\'')
		{
			(*length)++;
			(*index)++;
		}
		(*length)++;
		(*index)++;
		if (!input[*index] || ft_strchr(special_chars, input[*index]))
			return (input + *index - *length);
	}
	return (0);
}

static char	*parse_double_quotes(char *input, int *index, size_t *length)
{
	const char special_chars[7] = "<>| \t\n\0";
	if (input[*index] == '\"')
	{
		(*length)++;
		(*index)++;
		while (input[*index] && input[*index] != '\"')
		{
			(*length)++;
			(*index)++;
		}
		(*length)++;
		(*index)++;
		if (!input[*index] || ft_strchr(special_chars, input[*index]))
			return (input + *index - *length);
	}
	return (0);
}

static char	*parse_word_or_operator(char *input, int *index, size_t *length)
{
	const char special_chars[7] = "<>| \t\n\0";
	if (ft_strchr(special_chars, input[*index]) && input[*index])
	{
		while (ft_strchr(special_chars, input[*index]) && input[*index])
		{
			(*length)++;
			(*index)++;
		}
		return input + *index - *length;
	}
	else if (input[*index] && input[*index] != '\'' && input[*index] != '\"')
	{
		while (!ft_strchr(special_chars, input[*index]) && input[*index] &&
			   input[*index] != '\'' && input[*index] != '\"')
		{
			(*length)++;
			(*index)++;
		}
		
		if (!input[*index] || (input[*index] != '\'' && input[*index] != '\"'))
			return input + *index - *length;
	}
	return NULL;
}

int	lexical_analyzer(t_token **tokens, char *input, t_env **env_lst)
{
	int		pos;
	int		token_count;
	size_t	length;
	char	*segment_start;

	pos = 0;
	token_count = 0;
	length = 0;
	while (input[pos])
	{
		segment_start = parse_single_quotes(input, &pos, &length);
		store_token(tokens, &token_count, &length, segment_start);	
		segment_start = parse_double_quotes(input, &pos, &length);
		store_token(tokens, &token_count, &length, segment_start);
		segment_start = parse_word_or_operator(input, &pos, &length);
		store_token(tokens, &token_count, &length, segment_start);
	}
	update_tokens(tokens, env_lst);
	return (0);
}


// int quotes_token_mal(t_token **tokens, char *str, int *i, size_t *len, char *quote)
// {
// 	t_token	*token;
// 	const char delimiter[7] = "|<> \n\t\0";
	
// 	(*len)++;
// 	(*i)++;
// 	// while (str[*i] != *quote && str[*i] != '\0')
// 	while (!ft_strchr(delimiter, str[*i]) && str[*i] != '\0')
// 	{
// 		(*len)++;
// 		(*i)++;
// 	}
// 	(*len)++;
// 	(*i)++;
// 	if (*len)
// 	{
// 		token = token_new(str, *i, *len, NO_TAG, *quote);
// 		if (!token)
// 			return (1);
// 		token_add_back(tokens, token);
// 		(*len) = 0;
// 	}
// 	return (0);
// }

// int delimiter_token_mal(t_token **tokens, char *str, int *i, size_t *len, char *quote)
// {
// 	t_token	*token;
// 	t_tags	tag;
// 	const char delimiter[7] = "|<> \n\t\0";
// 	const char tags[4] = "|<>\0";
	
// 	tag = NO_TAG;
// 	while (ft_strchr(delimiter, str[*i]) && str[*i])
// 	{
// 		if (ft_strchr(tags, str[*i]))
// 			tag = NEED_DECIDE;
// 		(*i)++;
// 		(*len)++;
// 	}
// 	if (*len)
// 	{
// 		token = token_new(str, *i, *len, tag, *quote);
// 		if (!token)
// 			return (1);
// 		token_add_back(tokens, token);
// 		(*len) = 0;
// 	}
// 	return (0);
// }

// int token_mal(t_token **tokens, char *str, int *i, size_t *len, char *quote)
// {
// 	t_token	*token;
// 	const char delimiter[7] = "|<> \n\t\0";
// 	const char quotes[3] = "\'\"\0";

// 	while (!ft_strchr(delimiter, str[*i]) && !ft_strchr(quotes, str[*i]) && \
// 	 str[*i])
// 	{
// 		(*i)++;
// 		(*len)++;
// 	}
// 	if (*len && str[*i] != '\'')
// 	{
// 		token = token_new(str, *i, *len, NO_TAG, *quote);
// 		if (!token)
// 			return (1);
// 		token_add_back(tokens, token);
// 		(*len) = 0;
// 	}
// 	return (0);
// }

// t_token	*token_last(t_token *lst)
// {
// 	t_token	*temp_lst;

// 	temp_lst = lst;
// 	if (temp_lst)
// 	{
// 		while (temp_lst->next != 0)
// 			temp_lst = temp_lst->next;
// 	}
// 	return (temp_lst);
// }

// int lexical_analyzer(t_token **tokens, char *str, t_env **env_lst)
// {
// 	int	i;
// 	const char delimiter[7] = "|<> \n\t\0";
// 	const char quotes[3] = "\'\"\0";
// 	size_t len;
// 	char quote;

// 	*tokens = 0;
// 	i = 0;
// 	len = 0;
// 	while (str[i] != 0)
// 	{
// 		if (!len)
// 			quote = str[i];
// 		if (ft_strchr(quotes, str[i]) && quotes_token_mal(tokens, str, &i, &len, &quote))
// 			return (1);
// 		if (ft_strchr(delimiter, str[i]) && delimiter_token_mal(tokens, str, &i, &len, &quote))
// 			return (1);
// 		if (!ft_strchr(delimiter, str[i]) && !ft_strchr(quotes, str[i]) && \
// 		token_mal(tokens, str, &i, &len, &quote))
// 			return (1);
// 	}
// 	if (update_tokens(tokens, env_lst))
// 		return (1);
// 	return (0);
// }