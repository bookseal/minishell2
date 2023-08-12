/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_env_replace_util.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gichlee <gichlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 21:55:38 by gichlee           #+#    #+#             */
/*   Updated: 2023/08/12 22:18:48 by gichlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	value_substr_to_env_value(t_token *token, int i, t_env *env, int len_envkey)
{
	char	*replaced_value;
	char	*temp_str;
	char	*temp_str2;

	if (env->tag == ENV_EXIT)
		replaced_value = ft_itoa(env->exit_status);
	else
		replaced_value = ft_strdup(env->value);
	token->value[i] = '\0';
	temp_str = ft_strjoin(token->value, replaced_value);
	free(replaced_value);
	temp_str2 = token->value + i + len_envkey + 1;
	replaced_value = ft_strjoin(temp_str, temp_str2);
	free(temp_str);
	free(token->value);
	token->value = replaced_value;
	token->quote_lo = update_quote_lo(token, env, i, len_envkey);
	if (!token->quote_lo)
		return (1);
	return (0);
}

void	remove_dollar_word(t_token *token, int *del_i, char *value_substr)
{
	char	*new;
	char	*old;
	int		old_len;

	old = token->value;
	old_len = ft_strlen(old);
	new = ft_calloc(ft_strlen(token->value), sizeof(char));
	ft_strlcpy(new, old, *del_i + 1);
	ft_strlcat(new, old + *del_i + ft_strlen(value_substr) + 1, old_len);
	free(token->value);
	token->value = new;
}
