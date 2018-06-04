# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: inazarin <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/19 21:06:58 by inazarin          #+#    #+#              #
#    Updated: 2018/05/20 15:54:38 by inazarin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = inazarin.filler

SRCS = filler.c \
		plateau_handle.c \
		piece_handle.c

OBJ =	$(SRCS:%.c=%.o)

FLAGS = -Wall -Wextra -Werror

HEADER = filler.h

all: $(NAME)

%.o:%.c
	gcc -I. $(FLAGS)  -c $< -o $@

$(NAME): $(OBJ) $(HEADER)
	make -C libft
	gcc -g $(FLAGS) $(OBJ) libft/libft.a -o $(NAME) -fsanitize=address

clean:
	make clean -C libft/
	rm -f $(OBJ)

fclean: clean
	make fclean -C libft/
	rm -f libft.a
	rm -f $(NAME)

re: fclean all