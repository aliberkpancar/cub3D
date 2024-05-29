NAME = cub3D

SOURCES = ./src/main.c ./src/map_parser.c ./src/map.c ./src/gnl/get_next_line.c ./src/gnl/get_next_line_utils.c

OBJECTS = $(SOURCES:.c=.o)

CC = clang

CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address

MLX = mlx/libmlx.a

LIBRARIES = -Lmlx -lmlx -framework OpenGL -framework AppKit

HEADERS = ./includes/cub3d.h ./includes/map_parser.h ./includes/get_next_line.h

all: $(NAME)

$(NAME): $(OBJECTS) $(MLX)
	$(CC) $(CFLAGS) $(LIBRARIES) $(OBJECTS) -o $(NAME)

$(MLX):
	make -C mlx

$(GNL):
	make -C includes

clean:
	rm -f $(OBJECTS)
	make -C mlx clean
	make -C includes clean

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re