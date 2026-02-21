# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: milija-h <milija-h@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/08 19:10:45 by milija-h          #+#    #+#              #
#    Updated: 2025/09/08 12:43:33 by milija-h         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
MAKEFLAGS += --no-print-directory

CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs
RM = rm -f
SRCS = 	ft_atoi.c \
	ft_bzero.c \
	ft_calloc.c \
	ft_isalnum.c \
	ft_isalpha.c \
	ft_isascii.c \
	ft_isdigit.c \
	ft_isprint.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_memcpy.c \
	ft_memmove.c \
	ft_memset.c \
	ft_putchar_fd.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c \
	ft_putstr_fd.c \
	ft_strchr.c \
	ft_strdup.c \
	ft_striteri.c \
	ft_strjoin.c \
	ft_strlcat.c \
	ft_strlcpy.c \
	ft_strlen.c \
	ft_strmapi.c \
	ft_strncmp.c \
	ft_strnstr.c \
	ft_strrchr.c \
	ft_strtrim.c \
	ft_substr.c \
	ft_tolower.c \
	ft_toupper.c \
	ft_itoa.c \
	ft_split.c \
	ft_printf.c \
	ft_print_d.c \
	ft_print_i.c \
	ft_print_u.c \
	ft_print_x.c \
	ft_print_X.c \
	ft_print_char.c \
	ft_print_string.c \
	ft_print_percent.c \
	ft_print_pointer.c \
	ft_isprint.c \
	ft_atol.c \
	ft_realloc.c \
	get_next_line.c \
	gnl_utils.c \
	ft_strcmp.c \
	array_len.c \
	ft_strcat.c \
	ft_strcpy.c \
	ft_strncpy.c \
	ft_isspace.c \
	ft_strndup.c \
	ft_isoperator.c \
	ft_atoll.c 

SRCSB = ft_lstnew_bonus.c ft_lstlast_bonus.c ft_lstadd_front_bonus.c ft_lstadd_back_bonus.c ft_lstsize_bonus.c ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c \
get_next_line_utils.c

OBJS = $(SRCS:.c=.o)
OBJSB = $(SRCSB:.c=.o)
NAME = libft.a

%.o: %.c 
	@$(CC) $(CFLAGS) -c $< -o $@
all: $(NAME)

bonus: $(OBJSB)
	@$(AR) $(NAME) $(OBJSB)
	touch bonus
	
$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)

clean:
	@$(RM) $(OBJS) $(OBJSB) bonus
	
fclean: clean
	@$(RM) $(NAME)
	
re: fclean all

.PHONY: all clean fclean re
