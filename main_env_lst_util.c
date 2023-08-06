#include "main.h"

void	env_lstdelone(t_env *lst, void (*del)(void *))
{
	if (lst == 0 || del == 0)
		return ;
	del(lst->key);
	del(lst->value);
	free(lst);
}

void	env_lstclear(t_env **lst, void (*del)(void *))
{
	t_env	*next_lst;

	if (*lst == 0 || del == 0)
		return ;
	while (*lst != 0)
	{
		next_lst = (*lst)->next;
		env_lstdelone(*lst, del);
		*lst = next_lst;
	}	
}

t_env	*env_lstnew_malloc(char *key, char *value)
{
	t_env	*new_lst;

	new_lst = (t_env *)ft_calloc(1, sizeof(t_env));
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
