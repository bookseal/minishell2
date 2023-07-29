/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gichlee <gichlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 15:44:57 by gichlee           #+#    #+#             */
/*   Updated: 2022/12/18 15:04:38 by gichlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalpha(int c)
{
	if (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z'))
		return (1);
	else
		return (0);
}

/*
int	ft_isalpha(int c)
{
	unsigned char	ch;

	ch = (unsigned char)c;
	if (0 <= ch && ch <= 255)
	{	
		if (('a' <= ch && ch <= 'z') || ('A' <= ch && ch <= 'Z'))
			return (1);
	}
	return (0);
}
*/
