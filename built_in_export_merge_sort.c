#include "main.h"

#include <stdbool.h>

t_env* SortedMerge(t_env* a, t_env* b);
void FrontBackSplit(t_env* source, t_env** frontRef, t_env** backRef);

// Merge Sort function for linked list
void env_merge_sort(t_env** headRef)
{
	t_env* head = *headRef;
	t_env* a;
	t_env* b;

	if ((head == NULL) || (head->next == NULL))
	{
		return;
	}

	FrontBackSplit(head, &a, &b);

	env_merge_sort(&a);
	env_merge_sort(&b);

	*headRef = SortedMerge(a, b);
}

// Helper function to merge two sorted lists
t_env* SortedMerge(t_env* a, t_env* b)
{
	t_env* result = NULL;

	if (a == NULL)
		return b;
	else if (b == NULL)
		return a;

	if (strcmp(a->key, b->key) <= 0)
	{
		result = a;
		result->next = SortedMerge(a->next, b);
	}
	else
	{
		result = b;
		result->next = SortedMerge(a, b->next);
	}

	return result;
}

// Helper function to split the list into two halves
void FrontBackSplit(t_env* source, t_env** frontRef, t_env** backRef)
{
	t_env* fast;
	t_env* slow;

	if (source == NULL || source->next == NULL)
	{
		*frontRef = source;
		*backRef = NULL;
	}
	else
	{
		slow = source;
		fast = source->next;

		while (fast != NULL)
		{
			fast = fast->next;
			if (fast != NULL)
			{
				slow = slow->next;
				fast = fast->next;
			}
		}

		*frontRef = source;
		*backRef = slow->next;
		slow->next = NULL;
	}
}

t_env* env_dup(t_env* head) {
	
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