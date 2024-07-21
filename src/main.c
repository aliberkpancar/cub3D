#include "cub3d.h"
#include <stdbool.h>
#include <stdio.h>

static bool	is_cub_extension(char *file)
{
	int	i;

	i = 0;
	if (ft_strlen(file) < 5)
		return (false);
	while (file[i])
		i++;
	if (file[i - 1] != 'b' || file[i - 2] != 'u' || file[i - 3] != 'c' || \
		file[i - 4] != '.')
		return (false);
	return (true);
}

static int	close_window(t_vars *vars)
{
	mlx_destroy_window(vars->mlx.mlx, vars->mlx.win.win);
	exit(0);
}

int	main(int argc, char **argv)
{
	//flood fill
	//headers will change
	// multiple map
	// Makefile wildcard
	// if (ray_len == 0) draw.c:96
	// check ability of lock xpms?
	// when change texture segfault
	//if (ray_len == 0) //ask bg
	t_vars	vars;

	if (argc != 2)
		return (printf("Error\nInvalid argument\n"), 1);
	if (is_cub_extension(argv[1]) == false)
		return (printf("Error\nExtension should be '.cub'\n"), 1);
	init_game(&vars, argv[1]);
	mlx_hook(vars.mlx.win.win,
		KeyPress, (1 << 0), key_press_handler, &vars);
	mlx_hook(vars.mlx.win.win,
		KeyRelease, (1 << 1), key_release_handler, &vars);
	mlx_hook(vars.mlx.win.win,
		Destroy, (1 << 17), key_release_handler, &vars);
	mlx_hook(vars.mlx.win.win, 17, 0, close_window, &vars);
	mlx_loop_hook(vars.mlx.mlx, update, &vars);
	mlx_loop(vars.mlx.mlx);
	return (0);
}
	
	