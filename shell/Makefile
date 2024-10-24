# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mabdelna <mabdelna@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/02 14:22:36 by mabdelna          #+#    #+#              #
#    Updated: 2024/10/02 14:22:37 by mabdelna         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = minishell

LIBFT       = libft.a
LIBFT_PATH  = libraries/libft

CC          = cc
CFLAGS      = -Wall -Werror -Wextra -Iinclude

SRCS        = builtins/cd.c builtins/echo.c builtins/env_utils.c builtins/env.c builtins/exit.c builtins/export.c\
              builtins/pwd.c builtins/unset.c execute/execute_error_msg.c execute/execute_builtin.c execute/execute_redirect.c \
              execute/execute_utils.c execute/execute.c execute/exist_check.c execute/execute_simple_cmd.c execute/ft_get_path.c\
              execute/ft_init_tree.c expand/ft_expand_utils.c expand/ft_expand.c expand/ft_expander_split.c \
              expand/ft_strip_quotes.c expand/ft_heredoc_expander.c tokenize/tokenize.c parse/parse_clear.c\
              parse/parse_error.c parse/parse_nodes.c parse/parse_utils.c parse/parse.c tokenize/tokenize_helper.c\
              tokenize/tokenize_list.c tokenize/tokenize_utils.c main_utils/ft_clean.c main_utils/ft_signals.c main.c 

OBJS        = $(SRCS:.c=.o)

READLINE_PATH = $(HOME)/.local

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@ -I$(READLINE_PATH)/include

all: $(NAME)

$(LIBFT):
	@make -C $(LIBFT_PATH)

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) -o $(NAME) $(OBJS) -L$(READLINE_PATH)/lib -lreadline -L$(LIBFT_PATH) -lft

clean:
	@make clean -C $(LIBFT_PATH)
	@rm -f $(OBJS)

fclean: clean
	@make fclean -C $(LIBFT_PATH)
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
