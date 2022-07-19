# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: shabibol <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/02 17:41:06 by shabibol          #+#    #+#              #
#    Updated: 2022/07/02 17:41:08 by shabibol         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = FDF

LIBFT = ./Libft/libft.a
PRINTF = ./printf/libftprintf.a

SRCS = fdf.h main.c different_method.c mlx_practice.c matrix_function.c parsing.c get_next_line.c get_next_line_utils.c


OBJS = $(SRCS:%.c=%.o)

FLAGS = -Wall -Wextra -g3
# -Werror -g3

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C ./Libft
	$(MAKE) -C ./printf
	gcc $(OBJS) -L minilibx-linux -lmlx -lXext -lX11 -lm -o $(NAME) $(PRINTF) $(LIBFT)

%.o: %.c
	gcc $(FLAGS) -I/usr/include -Imlx_linux -O3 -c $< -o $@

clean:
	rm -f *.o
	$(MAKE) clean -C ./Libft
	$(MAKE) clean -C ./printf

fclean: clean
	rm -rf $(NAME)
	$(MAKE) fclean -C ./Libft
	$(MAKE) fclean -C ./printf

re: fclean all
