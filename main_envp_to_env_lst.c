#include "main.h"

t_env	*env_lstnew(char *key, char *value)
{
	t_env	*new_lst;

	new_lst = (t_env *)malloc(sizeof(t_env) * 1);
	if (new_lst == 0)
		return (0);
	new_lst->key = ft_strdup(key);
	new_lst->value = ft_strdup(value);
	new_lst->next = 0;
	return (new_lst);
}

void	env_lstadd_back(t_env **lst, t_env *new)
{
	t_env	*head;
	t_env	*temp_lst;

	head = *lst;
	if (head == 0)
		*lst = new;
	else
	{
		temp_lst = head;
		while (temp_lst->next != 0)
			temp_lst = temp_lst->next;
		temp_lst->next = new;
	}
}

int envp_to_env_lst(char **envp, t_env **env_lst)
{
	int	i;
	while ((*envp)[i])
	{
		// TODO: split '='
		// TODO: ft_lstnew
		// ft_lstnew()
		// TODO: env_lst->key
		// TODO: env_lst->value
		// TODO: ft_lst_add_back
		i++;
	}
	return (0);
}