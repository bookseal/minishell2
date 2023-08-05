#include "main.h"

void	token_delone(t_token *lst, void (*del)(void *))
{
	if (lst == 0 || del == 0)
		return ;
	del(lst->value);
	del(lst->quote_lo);
	free(lst);
}

void	token_clear(t_token **lst, void (*del)(void *))
{
	t_token	*next_lst;

	if (*lst == 0 || del == 0)
		return ;
	while (*lst != 0)
	{
		next_lst = (*lst)->next;
		token_delone(*lst, del);
		*lst = next_lst;
	}	
}

void	token_add_back(t_token **lst, t_token *new)
{
	t_token	*head;
	t_token	*temp_lst;

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

t_token	*token_new(char *str, int i, size_t len, t_tags tag, char quote)
{
	t_token	*new_lst;
	size_t	start;

	new_lst = (t_token *)ft_calloc(1, sizeof(t_token));
	if (new_lst == 0)
		return (0);
	if (i < len)
		start = 0;
	else
		start = i - len;
	new_lst->value = ft_substr(str, start, len);
	new_lst->tag = tag;
	if (quote == '\'')
		new_lst->quote = SINGLE;
	else if (quote == '\"')
		new_lst->quote = DOUBLE;
	else
		new_lst->quote = NO_QUOTE;
	new_lst->quote_lo = (char *)ft_calloc(ft_strlen(new_lst->value), sizeof(char));
	new_lst->next = 0;
	return (new_lst);
}
