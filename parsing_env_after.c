#include "main.h"

char	*update_quote_lo(t_token *token, t_env *env, int start_i, int len_envkey)
{
	char	*replaced_quote;
	char	*new_blank_quote;
	char	*temp_str;
	
	new_blank_quote = ft_calloc(ft_strlen(env->value) + 1 , sizeof(char));
	if (new_blank_quote == 0) 
		return (0);
	ft_memset(new_blank_quote, '2', ft_strlen(env->value));
	token->quote_lo[start_i] = '\0';
	temp_str = ft_strjoin(token->quote_lo, new_blank_quote);
	free(new_blank_quote);
	replaced_quote = ft_strjoin(temp_str, token->quote_lo + start_i + len_envkey + 1);
	free(temp_str);
	free(token->quote_lo);
	return (replaced_quote);
}

t_env	*initialize_variable(int quote)
{
	t_env	*tmp;
	
	tmp = (t_env *)malloc(sizeof(t_env) * 1);
	if (!tmp)
		return (0);
	tmp->key = (char *)malloc(sizeof(char) * 2);
	if (!tmp->key)
		return (0);
	if (quote == 1)
		tmp->key[0] = '1';
	else
		tmp->key[0] = '0';
	tmp->key[1] = '\0';
	tmp->next = 0;
	return (tmp);
}

void	create_variable_value(t_token *tokens, int *i, int j, t_env *tmp)
{
	if ((j - *i) == 1 && (tmp->key[0] == '1' || \
			(tokens->value[j] != '\"' && tokens->value[j] != '\'')))
		tmp->value = (char *)malloc(sizeof(char) * 2);
	else
		tmp->value = (char *)malloc(sizeof(char) * 1);
	if (!tmp->value)
		return ;
	if ((j - *i) == 1 && (tmp->key[0] == '1' || \
			(tokens->value[j] != '\"' && tokens->value[j] != '\'')))
	{
		tmp->value[0] = '$';
		tmp->value[1] = '\0';
	}
	else
		tmp->value[0] = '\0';
}
