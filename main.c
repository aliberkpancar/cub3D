#include "./mlx/mlx.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "cub3d.h"

int main(int ac, char *av[])
{
	
	t_game	*game;
	//todo(apancar): handle .cub file
	if (ac != 2)
		return (1); // todo(apancar): throw error
	game = (t_game *)malloc(sizeof(t_game));
	if (!game)
		return (1); // todo(apancar): throw error
	init_game(game, av[1]);
	int i = 0;
	while (game->map[i])
	{	
		printf("i : %d = %s\n", i, game->map[i]);
		i++;	
	}
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, 800, 600, "cub3d");
	key_press(game, 13);
	// Move forward to avoid segfault
	mlx_hook(game->win, 2, 1L << 0, key_press, game->cam);
	mlx_loop(game->mlx);
	return (0);
}

