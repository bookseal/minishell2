/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_b_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gichlee <gichlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 18:35:42 by gichlee           #+#    #+#             */
/*   Updated: 2022/12/11 15:03:32 by gichlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (lst == 0 || del == 0)
		return ;
	del(lst->content);
	free(lst);
}

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*next_lst;

	if (*lst == 0 || del == 0)
		return ;
	while (*lst != 0)
	{
		next_lst = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = next_lst;
	}	
}

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*temp_lst;

	if (lst == 0 || f == 0)
		return ;
	temp_lst = lst;
	while (temp_lst != 0)
	{
		f(temp_lst->content);
		temp_lst = temp_lst->next;
	}
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*old_lst;
	t_list	*new_lst;
	t_list	*head;

	if (lst == 0 || f == 0 || del == 0)
		return (0);
	old_lst = lst;
	new_lst = ft_lstnew(f(old_lst->content));
	if (new_lst == 0)
		return (0);
	head = new_lst;
	old_lst = old_lst->next;
	while (old_lst != 0)
	{
		new_lst->next = ft_lstnew(f(old_lst->content));
		if (new_lst->next == 0)
		{
			ft_lstclear(&head, del);
			return (0);
		}
		new_lst = new_lst->next;
		old_lst = old_lst->next;
	}
	return (head);
}
