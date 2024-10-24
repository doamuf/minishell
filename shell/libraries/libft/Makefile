# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mabdelna <mabdelna@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/02 14:20:24 by mabdelna          #+#    #+#              #
#    Updated: 2024/10/02 14:20:49 by mabdelna         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = cc
CFLAGS = -Wall -Werror -Wextra

SRCS =  ft_bzero.c ft_calloc.c ft_free_char2.c ft_isalnum.c ft_isspace.c\
		ft_itoa.c ft_memcpy.c ft_memset.c ft_putchar_fd.c ft_putnbr_fd.c\
		ft_putstr_fd.c ft_split.c ft_strchr.c ft_strcmp.c ft_strdup.c\
		ft_strjoin_f.c ft_strjoin_with_f.c ft_strjoin_with.c ft_strjoin.c\
		ft_strlcpy.c ft_strlen.c ft_strncmp.c ft_strnstr.c ft_substr.c\
		ft_isalpha.c ft_isdigit.c ft_lstnew.c ft_lstadd_back.c ft_lstclear.c\

OBJS = $(SRCS:.c=.o)

INCLUDE_DIR := "../../include"

%.o: %.c
	@$(CC) -g $(CFLAGS) -c $< -I$(INCLUDE_DIR) -o $@

all: $(NAME)

$(NAME): $(OBJS)
	@ar -rcs $(NAME) $(OBJS)

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all
