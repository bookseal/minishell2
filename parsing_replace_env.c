#include "main.h"

/* This function replaces the token value and quote with new value and quote. */
static int replace_token(t_token *tokens, int i, int j, t_env *env_lst)
{
	char	*new_value;
	char	*new_blank;
	char	*new_str;

	/* Copy environment value and join with token value */
	new_value = ft_strdup(env_lst->value);
	tokens->value[i] = '\0';
	new_str = ft_strjoin(tokens->value, new_value);
	free(new_value);
	new_value = ft_strjoin(new_str, tokens->value + j);
	free(new_str);

	/* Replace old token value with new one */
	free(tokens->value);
	tokens->value = new_value;

	/* Allocate memory for new quote and initialize it with '2' */
	new_blank = (char *)malloc(sizeof(char) * (ft_strlen(env_lst->value) + 1));
	if (new_blank == 0)
		return (-1);
	new_blank[ft_strlen(env_lst->value)] = '\0';
	ft_memset(new_blank, '2', ft_strlen(env_lst->value));

	/* Join new quote with old one */
	tokens->quote_lo[i] = '\0';
	new_str = ft_strjoin(tokens->quote_lo, new_blank);
	free(new_blank);
	new_blank = ft_strjoin(new_str, tokens->quote_lo + j);
	free(new_str);

	/* Replace old quote with new one */
	free(tokens->quote_lo);
	tokens->quote_lo = new_blank;

	return (0);
}

/* This function handles the case when no matching environment variable is found. */
static int handle_not_found(t_token *tokens, int *i, int j, int quote)
{
	t_env	*tmp;
	int		res;

	/* Allocate memory for new variable */
	tmp = (t_env *)malloc(sizeof(t_env) * 1);
	if (tmp == 0)
		return (-1);

	/* Allocate memory for variable key and set it */
	tmp->key = (char *)malloc(sizeof(char) * 2);
	if (tmp->key == 0)
		return (-1);
	tmp->key[0] = (quote == 1) ? '1' : '0';
	tmp->key[1] = '\0';

	/* Allocate memory for variable value and set it */
	tmp->value = (char *)malloc(sizeof(char) * ((j - *i) == 1 && (tmp->key[0] == '1' || \
		(tokens->value[j] != '\"' && tokens->value[j] != '\'')) ? 2 : 1));
	if (tmp->value == 0)
		return (-1);
	if ((j - *i) == 1 && (tmp->key[0] == '1' || \
		(tokens->value[j] != '\"' && tokens->value[j] != '\'')))
	{
		tmp->value[0] = '$';
		tmp->value[1] = '\0';
	}
	else
		tmp->value[0] = '\0';

	tmp->next = 0;

	/* Replace the token with new variable and adjust the index i */
	res = replace_token(tokens, *i, j, tmp);
	if (!((j - *i) == 1 && (tmp->key[0] == '1' || \
		(tokens->value[j] == '\"' || tokens->value[j] != '\''))))
		*i = *i - 1;

	/* Delete the temporary variable */
	env_delone(tmp, &free);

	return (res);
}

/* This function searches for environment variable and replaces it in the token. */
static int search_and_replace(t_token *t, int *i, t_env *env_lst, int q)
{
	char	*new_str;
	int		j;

	/* Find the end of variable key in the token */
	j = *i + 1;
	while (t->value[j] != ' ' && t->value[j] != '\0' && t->value[j] != '\t' && \
		t->value[j] != '\"' && t->value[j] != '\'' && t->value[j] != '/' \
		&& t->value[j] != '$' && t->value[j] != '=')
		j++;

	/* Copy the variable key from the token */
	new_str = ft_substr(t->value, *i + 1, j - *i - 1);

	/* Search for the variable in the environment list */
	while (env_lst != 0)
	{
		if (ft_strncmp(env_lst->key, new_str, ft_strlen(new_str) + 1) == 0)
			break;
		env_lst = env_lst->next;
	}

	/* Handle the case when variable key is empty */
	if (new_str[0] == '\0')
	{
		free(new_str);
		return (0);
	}

	free(new_str);

	/* If the variable is found, replace it in the token; otherwise, handle the not found case */
	return (env_lst != 0) ? replace_token(t, *i, j, env_lst) : handle_not_found(t, i, j, q);
}

void	replace_env(t_token *tokens, t_env *env_lst)
{
	int	i;
	
	i = 0;
	while (tokens->value[i] != '\0')
	{
		if (tokens->value[i] == '\'')
		{
			i++;
			while (tokens->value[i] != '\'' && tokens->value[i] != '\0')
				i++;
		}
		else if (tokens->value[i] == '\"')
		{
			while (tokens->value[++i] != '\"')
				if (tokens->value[i] == '$')
					search_and_replace(tokens, &i, env_lst, 1);
		}
		else if (tokens->value[i] == '$')
			search_and_replace(tokens, &i, env_lst, 0);
		i++;
	}
}