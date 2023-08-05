#include "main.h"

int	value_substr_to_env_value(t_token *token, int start_i, t_env *env, int len_envkey)
{
	char	*replaced_value;
	char	*temp_str;
	char	*temp_str2;

	replaced_value = ft_strdup(env->value);
	token->value[start_i] = '\0';
	temp_str = ft_strjoin(token->value, replaced_value);
	free(replaced_value);
	temp_str2 = token->value + start_i + len_envkey + 1;
	replaced_value = ft_strjoin(temp_str, temp_str2);
	free(temp_str);
	free(token->value);
	token->value = replaced_value;
	token->quote_lo = update_quote_lo(token, env, start_i, len_envkey);
	if (!token->quote_lo)
		return (1);
	return (0);
}

int	dollar_to_env(t_token *token, int *start_i, t_env *env_lst)
{
	char	*value_substr;
	int		len_envkey;
	t_env	*env;

	len_envkey = get_len_envkey(token, *start_i);
	value_substr = ft_substr(token->value, *start_i + 1, len_envkey);
	env = get_env_value(value_substr, env_lst);
	if (env == 0)
		return (1);
	if (value_substr_to_env_value(token, *start_i, env, len_envkey))
		return (1);
	return (0);
}

int	handle_double_quote(t_token *token, t_env *env_lst, int *i)
{
	(*i)++;
	while (*i < ft_strlen(token->value) && token->value[*i] != '\"')
	{
		if (token->value[*i] == '$' && dollar_to_env(token, i, env_lst))
			return (1);
		(*i)++;
	}
	return (0);
}

int	handle_single_quote(t_token *token, int *i)
{
	(*i)++;
	while (*i < ft_strlen(token->value) && token->value[*i] != '\'')
		(*i)++;
	return (0);
}

void	replace_env(t_token *tokens, t_env *env_lst)
{
	int		start_i;
	char	c;
	char	front;
	
	while (tokens)
	{	
		start_i = 0;
		c = tokens->value[start_i];
		front = c;
		while (c)
		{
			c = tokens->value[start_i];
			if (front == '\'' && handle_single_quote(tokens, &start_i))
				;
			else if (front == '\"' && handle_double_quote(tokens, env_lst, &start_i))
				no_env_matched(0, 0, 0, 1);
			else if (c == '$' && dollar_to_env(tokens, &start_i, env_lst))
				no_env_matched(0, 0, 0, 0);
			start_i++;
		}
		tokens = tokens->next;
	}
}