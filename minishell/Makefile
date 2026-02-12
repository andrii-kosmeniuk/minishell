# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: milija-h <milija-h@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/19 19:13:22 by milija-h          #+#    #+#              #
#    Updated: 2026/01/16 21:31:29 by milija-h         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAKEFLAGS += --no-print-directory

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LDLIBS  = -lreadline -lncurses

NAME = minishell

SRC = srcs/env/get_envp.c \
	srcs/utils/utils.c \
	srcs/utils/utils2.c \
	srcs/utils/utils3.c \
	srcs/utils/utils4.c \
	srcs/env/env_utils.c \
	srcs/clean_up/free_utils.c \
	srcs/clean_up/free_utils2.c \
	srcs/debug/debug.c \
	srcs/signals/signal_handlers.c \
	srcs/signals/signal_utils.c \
	srcs/init/init.c \
	srcs/lexer/lexer.c \
	srcs/lexer/lexer_utils.c \
	srcs/lexer/lex_redir_and_pipe.c \
	srcs/lexer/lex_word_and_quotes.c \
	srcs/parser/parser.c \
	srcs/parser/parser_clean_up.c \
	srcs/parser/parser_utils.c \
	srcs/parser/redir_utils.c \
	srcs/execution/heredoc/here_doc.c \
	srcs/execution/error_handling/error_handling.c \
	srcs/execution/execution/execute_in_child.c \
	srcs/execution/execution/execution.c \
	srcs/execution/heredoc/close_fds.c \
	srcs/execution/execution/execution_utils.c \
	srcs/execution/exit_code/calc_exit_code.c \
	srcs/execution/pipes/pipes.c \
	srcs/execution/pipes/pipes_utils.c \
	srcs/execution/pipes/execute_pipeline.c \
	srcs/execution/redirections/fd_utils.c \
	srcs/execution/redirections/redirection_utils.c \
	srcs/execution/utils/signal_handling.c \
	srcs/execution/built_ins/built_ins.c \
	srcs/execution/built_ins/builtin_utils.c \
	srcs/execution/built_ins/builtin_utils2.c \
	srcs/execution/heredoc/heredoc_utils.c \
	srcs/expansions/expand_input_string.c \
	srcs/expansions/expander_utils.c \
	srcs/expansions/word_splitting.c \
	srcs/expansions/main_expander.c \
	srcs/syntax/syntax_check.c \
	srcs/main/main_utils.c \
	main.c

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
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(LDLIBS) -o $(NAME)
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

