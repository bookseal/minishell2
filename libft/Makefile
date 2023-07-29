# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gichlee <gichlee@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/05 20:07:37 by gichlee           #+#    #+#              #
#    Updated: 2022/12/18 14:54:28 by gichlee          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar
ARFLAGS = -rcs
HEADER = -I ./libft.h
ifndef BONUS
	OBJS = $(OBJS_MANDATORY)
else
	OBJS = $(OBJS_MANDATORY) $(OBJS_BONUS)
endif
OBJS_MANDATORY = ft_isalpha.o ft_isdigit.o ft_isalnum.o ft_isascii.o ft_isprint.o \
ft_strlen.o ft_memset.o ft_bzero.o ft_memcpy.o ft_memmove.o \
ft_strlcpy.o ft_strlcat.o ft_toupper.o ft_tolower.o \
ft_strchr.o ft_strrchr.o ft_strncmp.o ft_memchr.o ft_memcmp.o \
ft_strnstr.o ft_atoi.o ft_calloc.o ft_strdup.o \
ft_substr.o ft_strjoin.o ft_strtrim.o ft_split.o ft_itoa.o ft_strmapi.o ft_striteri.o \
ft_putchar_fd.o ft_putstr_fd.o ft_putendl_fd.o ft_putnbr_fd.o 
OBJS_BONUS = ft_lst_a_bonus.o ft_lst_b_bonus.o
SRCS = $(OBJS:%.o=%.c)
$(NAME): $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

$(OBJS): $(SRCS)
	$(CC) $(CFLAGS) -c $^ $(HEADER)

all: $(NAME)

clean:
	rm -f *.o

fclean:
	rm -f *.o $(NAME)

re: fclean all

bonus: 
	make BONUS=1 all
	

.PHONY: all clean fclean re bonus