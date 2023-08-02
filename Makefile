NAME		= minishell
SRCS		= $(wildcard *.c)
OBJS		= $(patsubst ./%.c, ./%.o, $(SRCS))
CC			= cc
#CFALGS		= -Wall -Wextra -Werror
CFALGS		= -g -fsanitize=address
LIBFT		= libft
LINKERS		= -lft -L$(LIBFT) -lreadline -L/Users/gichlee/.brew/opt/readline/lib
INCLUDES	= -I ./includes -I/Users/gichlee/.brew/opt/readline/include
RM			= rm -rf
.PHONY:		all clean fclean re
./%.o:		./%.c ./main.h
			$(CC) $(CFALGS) $(INCLUDES) -o $@ -c $<
all:		$(NAME)
$(NAME):	$(OBJS)
			$(MAKE) -C $(LIBFT) all
			$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LINKERS) -o $(NAME) -g
clean:
			make -C $(LIBFT) clean
			$(RM) $(TMP)
fclean:
			make clean
			make -C $(LIBFT) fclean
			$(RM) $(NAME)
re:			fclean all