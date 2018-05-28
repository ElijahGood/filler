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
		

OBJ =	$(SRCS:%.c=%.o)

FLAGS = -g -Wall -Wextra -Werror

HEADER = filler.h

all: $(NAME)

%.o:%.c
	gcc -I. $(FLAGS)  -c $< -o $@ 

$(NAME): $(OBJ) $(HEADER)
	make -C libft
	cp ./libft/libft.a ./$(NAME)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

clean:
	make clean -C libft/
	rm -f $(OBJ)

fclean: clean
	make fclean -C libft/
	rm -f libft.a
	rm -f $(NAME)

re: fclean all