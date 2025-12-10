# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abisani <abisani@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/12 16:38:03 by abisani           #+#    #+#              #
#    Updated: 2025/12/10 10:42:38 by abisani          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


.PHONY: all clean fclean re bonus test

CC = cc
CFLAGS = -g -Wall -Werror -Wextra

NAME = fractol
TEST_NAME = fractol_test

SRC_DIR = src
MAIN_FILES = main.c
TEST_FILES = test_main.c
SRC_FILES =
PRINTF_FILES = intlen.c put_unsnbr_fd.c ft_printf.c print_c.c print_s.c \
	print_p.c print_di.c print_u.c print_x.c print_x_cap.c ft_putnbr_fd.c

SRC = $(addprefix $(SRC_DIR)/, $(MAIN_FILES)) \
		$(addprefix $(SRC_DIR)/, $(SRC_FILES)) \
		$(addprefix printf/, $(PRINTF_FILES))

TEST_SRC = $(addprefix $(SRC_DIR)/, $(TEST_FILES)) \
		$(addprefix $(SRC_DIR)/, $(SRC_FILES)) \
		$(addprefix printf/, $(PRINTF_FILES))

OBJ = $(SRC:.c=.o)
TEST_OBJ = $(TEST_SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $^ -Lminilibx-linux -lmlx -lXext -lX11 -lm -o $(NAME)

%.o: %.c $(SRC_DIR)/fractol.h
	$(CC) $(CFLAGS) -Iminilibx-linux -c $< -o $@

clean:
	rm -f $(OBJ) $(TEST_OBJ)

fclean: clean
	rm -f $(NAME) $(TEST_NAME)

re: fclean all

$(TEST_NAME): $(TEST_OBJ)
	$(CC) $(CFLAGS) $^ -Lminilibx-linux -lmlx -lXext -lX11 -lm -o $(TEST_NAME)

