NAME = cub3D

CC = gcc

SRC = src

OBJ = obj

SRCS = 	$(SRC)/alize.c \
		$(SRC)/check_map.c \
		$(SRC)/controller.c \
		$(SRC)/draw.c \
		$(SRC)/error.c \
		$(SRC)/free.c \
		$(SRC)/game.c \
		$(SRC)/init.c \
		$(SRC)/main.c \
		$(SRC)/map.c \
		$(SRC)/parse_util.c \
		$(SRC)/parse_utils.c \
		$(SRC)/parse_vars.c \
		$(SRC)/parse.c \
		$(SRC)/player.c \
		$(SRC)/raycast_utils.c \
		$(SRC)/texture.c \
		$(SRC)/utils.c \
		$(SRC)/minimap.c \
		$(SRC)/minimap2.c

MLX = lib/mlx/libmlx.a

LIBFT = lib/libft/libft.a

GNL = lib/get_next_line/get_next_line.a

INCLUDES = -I./lib/mlx -I./lib/get_next_line -I./lib/libft -I./inc

CFLAGS = -O3 -Wall -Wextra -Werror -g

MLX_FLAGS_LINUX = $(GNL) $(LIBFT) $(MLX) -Bdynamic -L/usr/lib/X11 -lXext -lX11 -lm

MLX_FLAGS_MAC = $(GNL) $(LIBFT) $(MLX) -Bdynamic -framework OpenGL -framework AppKit

UNAME = $(shell uname)

ifeq ($(UNAME), Linux)
	MLX_FLAGS = $(MLX_FLAGS_LINUX)
else
	MLX_FLAGS = $(MLX_FLAGS_MAC)
endif

OBJS = $(SRCS:$(SRC)/%.c=$(OBJ)/%.o)

all: $(NAME)

$(OBJ)/%.o: $(SRC)/%.c | $(OBJ)
	@$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $^

$(OBJ):
	mkdir -p $(OBJ)

$(NAME): $(OBJS) $(MLX) $(LIBFT) $(GNL)
	@echo "Compiling CUB3D..."
	@$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJS) $(MLX_FLAGS)

$(MLX):
	@if [ ! -d "./lib/mlx" ]; then\
		if [ "$(UNAME)" = "Linux" ]; then\
			echo "Downloading MiniLib x For Linux...";\
			curl -s https://cdn.intra.42.fr/document/document/18343/minilibx-linux.tgz -o ./lib/mlx.tgz;\
		else\
			echo "Downloadig MiniLibx For MacOS...";\
			curl -s https://cdn.intra.42.fr/document/document/18344/minilibx_opengl.tgz -o ./lib/mlx.tgz;\
		fi;\
		mkdir ./lib/mlx;\
		tar xvfz ./lib/mlx.tgz --strip 1 -C ./lib/mlx > /dev/null 2> /dev/null;\
		rm ./lib/mlx.tgz;\
	fi;\
	if [ ! -f "./lib/mlx/libmlx.a" ]; then\
		echo "Compiling MiniLibx...";\
		make -C ./lib/mlx > /dev/null 2> /dev/null;\
	fi;

$(LIBFT):
	@echo "Compiling Libft..."
	@cd lib/libft && make USE_MATH=TRUE > /dev/null

$(GNL):
	@echo "Compiling get_next_line..."
	@cd lib/get_next_line && make > /dev/null

fclean: clean
	@rm -f $(NAME)

clean:
	@rm -f $(OBJ)/*.o
	@make -C lib/libft fclean > /dev/null
	@make -C lib/get_next_line fclean > /dev/null
	@if [ -d "./lib/mlx" ]; then make -C ./lib/mlx clean $2 > /dev/null 2> /dev/null;\
	fi
	@echo "All unnecessery files cleared."
re: fclean all

run: $(NAME)
	./$(NAME)

.PHONY: all re fclean clean run
