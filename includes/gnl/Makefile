# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aliberk <aliberk@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/19 13:59:14 by aliberk           #+#    #+#              #
#    Updated: 2024/05/19 13:59:20 by aliberk          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = get_next_line.a

CC = gcc

CFLAGS = -Wall -Wextra -Werror

FILES = get_next_line.c get_next_line_utils.c 

OBJ_FILES = $(FILES:.c=.o)

all: $(NAME)

$(NAME) : $(OBJ_FILES)
	ar rc $(NAME) $(OBJ_FILES)
	ranlib $(NAME)

clean :
	rm -f $(OBJ_FILES)

fclean : clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re