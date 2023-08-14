#include "minishell.h"

t_env*	env_dup(t_env* head)
{

	t_env* new_head = NULL, *tail = NULL;
	t_env* temp;

	if (head == NULL)
		return (NULL);
	while (head)
	{
		temp = env_lstnew_malloc(head->key, head->value);
		temp->tag = head->tag;
		if (new_head == NULL)
		{
			new_head = temp;
			tail = temp;
		}
		else
		{
			tail->next = temp;
			tail = temp;
		}
		head = head->next;
	}
	return new_head;
}
