# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abisani <abisani@student.42berlin.de>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/12 16:38:03 by abisani           #+#    #+#              #
#    Updated: 2025/12/23 13:03:42 by abisani          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


.PHONY: all clean fclean re bonus test

CC = cc
CFLAGS = -g -Wall -Werror -Wextra

NAME = fractol
LIBFT = libft/libft.a

SRC_DIR = src
MAIN_FILES = main.c
SRC_FILES = init.c fractals.c window_mgmt.c rendering.c utils.c

SRC = $(addprefix $(SRC_DIR)/, $(MAIN_FILES)) \
		$(addprefix $(SRC_DIR)/, $(SRC_FILES))

OBJ = $(SRC:.c=.o)
TEST_OBJ = $(TEST_SRC:.c=.o)

all: $(NAME)

$(LIBFT):
	@make -C libft

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $^ -Lminilibx-linux -lmlx -lXext -lX11 -lm -o $(NAME)

%.o: %.c $(SRC_DIR)/fractol.h
	$(CC) $(CFLAGS) -I. -c $< -o $@

clean:
	rm -f $(OBJ) $(TEST_OBJ)
	make -C libft clean

fclean: clean
	rm -f $(NAME) $(TEST_NAME)
	make -C libft fclean

re: fclean all
