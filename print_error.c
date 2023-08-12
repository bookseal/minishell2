/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gichlee <gichlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 21:47:31 by gichlee           #+#    #+#             */
/*   Updated: 2023/08/12 22:23:44 by gichlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	null_input_exit(void)
{
	ft_putendl_fd("exit", STDIN);
	return (1);
}

int	print_error(t_token *token, char *msg)
{
	ft_putstr_fd("minishell: syntax error ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd(" ", 2);
	if (token)
		ft_putendl_fd(token->value, 2);
	else
		ft_putendl_fd("", 2);
	return (1);
}

int	openfile_error(char *msg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(msg, 2);
	ft_putendl_fd(": No such file or directory", 2);
	return (1);
}
