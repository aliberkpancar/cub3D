trash="/dev/null"
if [ ! -d "./lib/mlx" ] && [ "$2" != "clean" ]; then
	if [ "$1" = "Linux" ]; then
		echo "Downloading MiniLibx For Linux..."
		curl -s https://cdn.intra.42.fr/document/document/18343/minilibx-linux.tgz -o ./lib/mlx.tgz
	else
		echo "Downloadig MiniLibx For MacOS..."
		curl -s https://cdn.intra.42.fr/document/document/18344/minilibx_opengl.tgz -o ./lib/mlx.tgz
	fi
	mkdir ./lib/mlx
	tar xvfz ./lib/mlx.tgz --strip 1 -C ./lib/mlx > $trash
	rm ./lib/mlx.tgz
fi
if [ ! -f "./lib/mlx/libmlx.a" ]; then
	echo "Compiling MiniLibx..."
	make -C ./lib/mlx > $trash 2> $trash
fi
