# NAME		= minishell
# SRCS		= $(wildcard *.c)
# OBJS		= $(patsubst ./%.c, ./%.o, $(SRCS))
# CC			= cc
# CFALGS		= -Wall -Wextra -Werror
# #CFLAGS		= -g -fsanitize=address
# LIBFT		= libft
# LINKERS		= -lft -L$(LIBFT) -lreadline -L/Users/jiwonle2/.brew/opt/readline/lib
# INCLUDES	= -I ./includes -I/Users/jiwonle2/.brew/opt/readline/include
# #MACBOOK
# #LINKERS		= -lft -L$(LIBFT) -lreadline -L/opt/homebrew/opt/readline/lib
# #INCLUDES	= -I ./includes -I/opt/homebrew/opt/readline/include
# RM			= rm -rf
# .PHONY:		all clean fclean re
# ./%.o:		./%.c ./main.h
# 			$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<
# all:		$(NAME)
# $(NAME):	$(OBJS)
# 			$(MAKE) -C $(LIBFT) all
# 			$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LINKERS) -o $(NAME) -g
# clean:
# 			make -C $(LIBFT) clean
# 			$(RM) $(TMP)
# fclean:
# 			make clean
# 			make -C $(LIBFT) fclean
# 			$(RM) $(NAME)
# re:			fclean all

NAME		= minishell
SRCS		= main.c \
				built_in_cd_util.c \
				built_in_cd.c \
				built_in_echo.c \
				built_in_env.c \
				built_in_exit.c \
				built_in_export_merge_sort.c \
				built_in_export.c \
				built_in_pwd.c \
				built_in_unset.c \
				execute_env_lst_to_envp.c \
				execute_parent.c \
				execute_pipex.c \
				execute_run_built_in.c \
				execute.c \
				exit_status.c \
				main_env_lst_util.c \
				main_envp_to_env_lst.c \
				main_signal.c \
				parsing_env_after.c \
				parsing_env_replace.c \
				parsing_env_replace_util.c \
				parsing_env_util.c \
				parsing_lexical_analyzer.c \
				parsing_lexical_assign_tags.c \
				parsing_lexical_divide_delimiters.c \
				parsing_lexical_quotes.c \
				parsing_lexical_quotes_util.c \
				parsing_lexical_token_util.c \
				parsing_lexical_update_tokens.c \
				parsing_syntax_built_in.c \
				parsing_syntax_cmd_util.c \
				parsing_syntax_create_argv.c \
				parsing_syntax_heredoc.c \
				parsing_syntax_locate_cmd_util.c \
				parsing_syntax_locate_cmd.c \
				parsing_syntax_redirection.c \
				parsing_syntax.c \
				parsing.c \
				print_error.c 

OBJS		= $(SRCS:%.c=%.o)
CC			= cc
CFLAGS		= -Wall -Wextra #-Werror
CFLAGS		+= -g -fsanitize=address
LIBFT		= libft
LINKERS		= -lft -L$(LIBFT) -lreadline -L/Users/gichlee/.brew/opt/readline/lib
INCLUDES	= -I ./includes -I/Users/gichlee/.brew/opt/readline/include
#MACBOOK
#LINKERS		= -lft -L$(LIBFT) -lreadline -L/opt/homebrew/opt/readline/lib
#INCLUDES	= -I ./includes -I/opt/homebrew/opt/readline/include
RM			= rm -rf

.PHONY:		all clean fclean re
%.o:		%.c ./main.h
			$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<
all:		$(NAME)

$(NAME):	$(OBJS)
			$(MAKE) -C $(LIBFT) all
			$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LINKERS) -o $(NAME)
clean:
			make -C $(LIBFT) clean
			$(RM) $(OBJS)
fclean:
			make clean
			make -C $(LIBFT) fclean
			$(RM) $(NAME)
re:			fclean all