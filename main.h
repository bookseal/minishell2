 /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gichlee <gichlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 13:17:26 by gichlee           #+#    #+#             */
/*   Updated: 2023/08/05 18:32:48 by gichlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <string.h>
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

# define STDIN 			0
# define STDOUT 		1
# define STDERR 		2
# define MIN_LEVEL		1
# define MAX_LEVEL		999
# define TRUE			1
# define FALSE			0

unsigned int	g_exit_status;

typedef enum e_tags {
	NO_TAG = 0,
	PIPE, // '|'
	REDIRECT_IN,  // '<'
	REDIRECT_OUT,  // '>'
	HEREDOC, // '<<'
	APPEND_OUT,  // '>>'
	REDIRECT_INFO,
	NEED_DECIDE,
} t_tags;

typedef enum e_built_in {
	NOT_BUILT_IN = 0,
	ECHO_CMD,
	CD_CMD,
	PWD_CMD,
	EXPORT_CMD,
	UNSET_CMD,
	ENV_CMD,
	EXIT_CMD,
} t_built_in;

typedef enum e_quotes {
	NO_QUOTE = 0,
	SINGLE,
	DOUBLE,
} t_quotes;

typedef enum e_env_tag {
	NO_ENV_TAG,
	ENV_EXIT,
	ENV_NO_VALUE,
} t_env_tag;

typedef struct s_env
{
	char			*key;
	char			*value;
	t_env_tag		tag;
	int				need_to_del;
	int				exit_status;
	struct s_env	*next;
}					t_env;

typedef struct s_token
{
	char			*value;
	t_tags			tag;
	t_quotes		quote;
	int				need_to_del;
	char			*quote_lo;
	struct s_token	*next;
}					t_token;

typedef struct s_cmd
{
	t_built_in		built_in;
	int				is_cmd;
	char			**argv;
	int				fd_in;
	int				fd_out;
	int				pipe_in;
	int				pipe_out;
	int				fd_in_origin;
	int				fd_out_origin;
	struct s_cmd	*next;
} 					t_cmd;

typedef struct s_info
{
	int		**fd;
	int		cmd_cnt;
}	t_info;

int	set_terminal(void);
void 	set_signal(void);
int 	envp_to_env_lst(char **envp, t_env **env_lst);
void	env_lstclear(t_env **lst, void (*del)(void *));
int		parsing(char *input, t_cmd **cmds, t_env **env_lst, t_info *info);
int		lexical_analyzer(t_token **tokens, char *input, t_env **env_lst);
t_token	*token_new(char *value, t_tags tag, char quote);
void	token_add_back(t_token **lst, t_token *new);
int	update_tokens(t_token **tokens, t_env **env_lst);
int divide_delimiters(t_token **tokens);
void	token_clear(t_token **lst, void (*del)(void *));
int assign_tags(t_token **tokens);
void	token_delone(t_token *lst, void (*del)(void *));
int	is_valid_quote_token(t_token **tokens);
int insert_quotes_location(t_token *tokens);
void	replace_env(t_token *tokens, t_env *env_lst);
void	env_delone(t_env *lst, void (*del)(void *));
t_env	*get_env_value(char *value_substr, t_env *env_lst);
char	*update_quote_lo(t_token *token, t_env *env, int i, int len_envkey);
int	get_len_envkey(t_token *token, int i);
void	remove_quotes(t_token *tokens);
void remove_quotes(t_token *tokens);
int	syntax_analyzer(t_cmd **cmds, t_token **tokens, t_env **env_lst, t_info *info);
int	print_error(t_token *token, char *msg);
int create_argv(t_cmd *cmd, t_token **tokens);
int	handle_redirection(t_token **tokens, t_cmd *cmds, t_env **env_lst);
void	unnecessary_token_delete(t_token **tokens);
int	handle_heredoc(t_token *token, t_cmd *cmd, t_env **env_lst);
int	is_built_in(char *argv_0);
char	*ft_strjoin_with_sep(char const *s1, char const *s2, char *sep);
void str_to_lowercase(char *str);
void	strs_free(char **strs);
int	locate_cmd(t_cmd *cmd, t_env *env_lst);
void	env_lstdelone(t_env *lst, void (*del)(void *));
void	env_lstclear(t_env **lst, void (*del)(void *));
t_env	*env_lstnew_malloc(char *key, char *value);
void	env_lstadd_back(t_env **lst, t_env *new);
int	null_input_exit(void);
int	set_terminal(void);
int	execute(t_cmd *cmds, t_env **env_lst, t_info *info);
void	strs_free(char **strs);
void	cmds_clear(t_cmd **cmds, void (*del)(void *));
int	run_built_in(t_cmd *cmds, t_env **env_lst);
void dup_in_and_out(t_cmd *tmp);
void	dup_and_close(t_cmd *cmd);
int built_in_echo(t_cmd *cmd, t_env **env_lst);
int	go_to_path(char *path, t_env **env_lst);
int built_in_cd(t_cmd *cmd, t_env **env_lst);
int built_in_pwd(t_env **env_lst);
int built_in_export(t_cmd *cmd, t_env **env_lst);
int	built_in_env(t_env **env_lst);
void pipex_gichlee(t_cmd *cmds, t_env **env_lst);
void print_argv(t_cmd *cmd, int i);
void	close_fd(t_cmd *cmds);
void	waiting(void);
int	is_key_name_error(char *key);
int built_in_unset(t_cmd *cmd, t_env **env_lst);
int built_in_exit(t_cmd *cmd, t_env **env_lst);
int	update_exit_status(t_env **env_lst, int status);
int	is_exit_status(t_env **env_lst, unsigned int *status);
void exit_to_env_lst(t_env *env_lst);
int	value_substr_to_env_value(t_token *token, int i, t_env *env, int len_envkey);
void	remove_dollar_word(t_token *token, int *del_i, char *value_substr);

/* pipex */
void	make_pipe(t_info *info, int cnt);
void	make_process(t_cmd *cmd, t_info *info, t_env **env_lst, int i);
void	execute_cmd(t_cmd *cmd, t_info *info, t_env **env_lst, int idx);
void	close_fds(t_info *info);
void	pipex(t_cmd *cmd, t_env **env_lst, t_info *info);
void	exec_built_in(t_cmd *cmd, t_env **env_lst);
void env_merge_sort(t_env** headRef);
t_env* env_dup(t_env* head);
int	env_lst_to_envp(t_env *env_lst, char ***envp);
int	openfile_error(char *msg);

#endif
