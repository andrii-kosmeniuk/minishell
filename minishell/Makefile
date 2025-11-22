# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: milija-h <milija-h@student.42vienna.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/19 19:13:22 by milija-h          #+#    #+#              #
#    Updated: 2025/11/19 19:13:23 by milija-h         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
MAKEFLAGS += --no-print-directory

CC = cc
CFLAGS = -Wall -Wextra -Werror

NAME = minishell

SRC = srcs/get_envp.c

OBJ = $(SRC:.c=.o)

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

SILENT ?=0
GREEN = \033[0;32m
PURPLE = \033[1;35m
CYAN = \033[0;36m
RED = \033[1;31m
RESET = \033[0m

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(LIBFT) $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(NAME): $(OBJ) $(LIBFT)
	@if [ "$(SILENT)" = "0" ]; then echo "$(GREEN)compiling...$(RESET)"; fi
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)
	@if [ "$(SILENT)" = "0" ]; then  echo "$(GREEN)ready to execute$(RESET)"; fi

clean:
	@if [ "$(SILENT)" = "0" ]; then echo "$(CYAN)deleting object files...$(RESET)"; fi
	@rm -f $(OBJ)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@if [ "$(SILENT)" = "0" ]; then echo "$(CYAN)done$(RESET)"; fi
fclean: clean
	@if [ "$(SILENT)" = "0" ]; then echo "$(RED)fully cleaning...$(RESET)"; fi
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@if [ "$(SILENT)" = "0" ]; then echo "$(RED)done$(RESET)"; fi
re:
	@echo "$(GREEN)re(making)...$(RESET)"
	@$(MAKE) SILENT=1 fclean
	@$(MAKE) SILENT=1 all
	@echo "$(GREEN)done, ready to execute again$(RESET)"

.PHONY: all clean fclean re

