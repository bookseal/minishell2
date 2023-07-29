/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leegichan <leegichan@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 17:23:05 by vismaily          #+#    #+#             */
/*   Updated: 2023/07/29 12:02:24 by leegichan        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include <termios.h>
# include <unistd.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

typedef enum s_tags {
    NO_REDIRECT = 0,
    REDIRECT_IN,  // '<'
	HEREDOC, // '<<'
    REDIRECT_OUT,  // '>'
    APPEND_OUT,  // '>>'
	PIPE, // '|'
	S_COLON, // ';'
} tags;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_token
{
	enum			tag;
	char			*value;
	char			*quote;
	struct s_token	*next;
}					t_token;

void set_signal(void);
int envp_to_env_lst(char **envp, t_env **env_lst);
#endif
