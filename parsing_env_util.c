#include "main.h"

int	get_len_envkey(t_token *token, int i)
{
	const char delimiter[7] = "|<> \n\t\0";
	const char quotes[3] = "\'\"\0";
	int		j;
	char	c;

	j = i + 1;
	c = token->value[j];
	if (ft_strchr(delimiter, c) || ft_strchr(quotes, c))
		return (0);
	while (1)
	{
		c = token->value[j];
		if (c == '=' || c == ' ' || c == '\0'  || c == '\t')
			break ;
		if (c == '\'' || c == '\"' || c == '$')
			break ;
		j++;
	}
	return (j - i - 1);
}

t_env	*get_env_value(char *value_substr, t_env *env_lst)
{
	t_env	*env;

	env = env_lst;
	while (env != 0)
	{
		if (!ft_strncmp(env->key, value_substr, ft_strlen(value_substr) + 1))
		{
			free(value_substr);
			return (env);
		}
		env = env->next;
	}
	if (value_substr[0] == '\0')
	{
		free(value_substr);
		return (0);
	}
	return (0);
}

void	env_delone(t_env *lst, void (*del)(void *))
{
	if (lst)
	{
		del(lst->key);
		del(lst->value);
		free (lst);
	}
}