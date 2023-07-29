/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_a_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gichlee <gichlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 15:47:37 by gichlee           #+#    #+#             */
/*   Updated: 2022/12/13 20:01:46 by gichlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new_lst;

	new_lst = (t_list *)malloc(sizeof(t_list) * 1);
	if (new_lst == 0)
		return (0);
	new_lst->content = content;
	new_lst->next = 0;
	return (new_lst);
}

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	t_list	*temp;

	if (lst == 0 || new == 0)
		return ;
	temp = *lst;
	*lst = new;
	(*lst)->next = temp;
}

int	ft_lstsize(t_list *lst)
{
	size_t	len;
	t_list	*temp_lst;

	temp_lst = lst;
	len = 0;
	while (temp_lst != 0)
	{
		len++;
		temp_lst = temp_lst->next;
	}
	return (len);
}

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*temp_lst;

	temp_lst = lst;
	if (temp_lst)
	{
		while (temp_lst->next != 0)
			temp_lst = temp_lst->next;
	}
	return (temp_lst);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*head;
	t_list	*temp_lst;

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
