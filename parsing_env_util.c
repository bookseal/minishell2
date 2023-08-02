#include "main.h"

void	env_delone(t_env *lst, void (*del)(void *))
{
	if (lst)
	{
		del(lst->key);
		del(lst->value);
		free (lst);
	}
}