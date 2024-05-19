NAME = cub3d

SOURCES = main.c camera.c init.c 

OBJECTS = $(SOURCES:.c=.o)

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g

MLX = mlx/libmlx.a

GNL = ./includes/gnl/get_next_line.a

LIBRARIES = -Lmlx -lmlx -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME): $(OBJECTS) $(MLX) $(GNL) 
	$(CC) $(CFLAGS) $(LIBRARIES) $(GNL) $(OBJECTS) -o $(NAME)  

$(MLX):
	make -C mlx

$(GNL):
	make -C includes/gnl

clean:
	rm -f $(OBJECTS)
	make -C mlx clean
	make -C includes/gnl clean

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re