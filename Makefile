NAME = cub3D

SOURCES = srcs/main.c srcs/parse.c srcs/render.c srcs/input.c gnl/get_next_line.c \
	gnl/get_next_line_utils.c srcs/texture.c

OBJECTS = $(SOURCES:.c=.o)

CC = clang

CFLAGS = -Wall -Wextra -Werror -g 

MLX = mlx/libmlx.a

LIBRARIES = -Lmlx -lmlx -framework OpenGL -framework AppKit

HEADERS = ./includes/cub3d.h

all: $(NAME)

$(NAME): $(OBJECTS) $(MLX)
	$(CC) $(CFLAGS) $(LIBRARIES) $(OBJECTS) -o $(NAME)

$(MLX):
	make -C mlx

clean:
	rm -f $(OBJECTS)
	make -C mlx clean

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re