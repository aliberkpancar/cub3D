NAME = libft.a

SRCS = \
	ft_atoi.c \
	ft_bzero.c \
	ft_calloc.c \
	ft_colors.c \
	ft_drawing.c \
	ft_itoa.c \
	ft_maps.c \
	ft_split.c \
	ft_strcat.c \
	ft_strchr.c \
	ft_strdup.c \
	ft_strjoin.c \
	ft_strlcat.c \
	ft_strlcpy.c \
	ft_strlen.c \
	ft_strncmp.c \
	ft_substr.c \
	ft_swap.c \
	ft_utils.c \
	ft_vec_float.c \
	ft_vec_op.c \
	ft_vec_vec.c 

CC = gcc

FLAGS = -Wall -Werror -Wextra -g

OBJECTS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): ${OBJECTS}
	ar -rcs $(NAME) $(OBJECTS)

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean re fclean math