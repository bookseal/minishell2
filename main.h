/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leegichan <leegichan@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 17:23:05 by vismaily          #+#    #+#             */
/*   Updated: 2023/08/03 23:41:09 by leegichan        ###   ########.fr       */
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
# include <stdbool.h>

# define STDIN 			0
# define STDOUT 		1
# define STDERR 		2

typedef enum s_tags {
	NO_TAG = 0,
	PIPE, // '|'
	REDIRECT_IN,  // '<'
	REDIRECT_OUT,  // '>'
	HEREDOC, // '<<'
	APPEND_OUT,  // '>>'
	REDIRECT_INFO,
	NEED_DECIDE,
} tags;

typedef enum s_quotes {
	NO_QUOTE = 0,
	SINGLE,
	DOUBLE,
} quotes;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_token
{
	char			*value;
	tags			tag;
	quotes			quote;
	bool			need_to_del;
	struct s_token	*next;
	char			*quote_lo;
}					t_token;

typedef struct s_cmd
{
	char			*path;
	char			**argv;
	struct s_cmd	*next;
} 					t_cmd;

void 	set_signal(void);
int 	envp_to_env_lst(char **envp, t_env **env_lst);
void	env_lstclear(t_env **lst, void (*del)(void *));
int		parsing(char *input, t_cmd **cmds, t_env **env_lst);
int		lexical_analyzer(t_token **tokens, char *input, t_env **env_lst);
t_token	*token_new(char *str, int i, size_t len, tags tag, char quote);
void	token_add_back(t_token **lst, t_token *new);
int	update_tokens(t_token **tokens, t_env **env_lst);
int divide_delimiters(t_token **tokens);
t_token	*token_new(char *str, int i, size_t len, tags tag, char quote);
void	token_clear(t_token **lst, void (*del)(void *));
int assign_tags(t_token **tokens);
void	token_delone(t_token *lst, void (*del)(void *));
int	is_valid_quote_token(t_token *tokens);
int insert_quotes_location(t_token *tokens);
void	replace_env(t_token *tokens, t_env *env_lst);
void	env_delone(t_env *lst, void (*del)(void *));
t_env	*get_env_value(char *value_substr, t_env *env_lst);
char	*update_quote_lo(t_token *token, t_env *env, int i, int len_envkey);
int	get_len_envkey(t_token *token, int i);
void	no_env_matched(t_token *token, int *start_i, int len_envkey, int quote);
void	remove_quotes(t_token *tokens);
void remove_quotes(t_token *tokens);
int	syntax_analyzer(t_cmd **cmds, t_token **tokens, t_env **env_lst);
int	print_error(t_token *token, char *msg);
int create_argv(t_cmd *cmd, t_token **tokens);
int	handle_redirection(t_token **tokens, t_cmd *cmds, t_env **env_lst);
void	unnecessary_token_delete(t_token **tokens);

#endif
