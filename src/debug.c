#include "cub3d.h"

void	init_debug(t_vars *vars)
{
	printf("Initializing debug window...\n");
	vars->debug.win.height = HEIGHT;
	vars->debug.win.width = WIDTH;
	vars->debug.win.win = mlx_new_window(vars->mlx.mlx,
			WIDTH, HEIGHT, "vars - map");
	vars->debug.image.image = mlx_new_image(vars->mlx.mlx,
			vars->mlx.win.width, vars->mlx.win.height);
	vars->debug.image.data = (t_color *)mlx_get_data_addr(vars->debug.image.image,
			&vars->debug.image.bits_per_pixel,
			&vars->debug.image.size_line, &vars->debug.image.endian);
	vars->debug.image.size_line /= 4;
}

void	draw_tile(t_image *debug, char tile, int x, int y)
{
	int	i;
	int	j;

	i = TILE_SIZE * x;
	while (i < TILE_SIZE * (x + 1) - 1)
	{
		j = (TILE_SIZE * y) + 1;
		while (j < TILE_SIZE * (y + 1) - 1)
		{
			if (tile == '1')
				ft_put_pixel(debug, i, j, g_black);
			else if (tile == '0')
				ft_put_pixel(debug, i, j, g_gray);
			j++;
		}
		i++;
	}
}

void	draw_map(t_vars *vars)
{
	int	i;
	int	j;

	i = 0;
	while (i < vars->map.size.x)
	{
		j = 0;
		while (j < vars->map.size.y)
		{
			draw_tile(&vars->debug.image,
				vars->map.tiles[i + vars->map.size.x * j], i, j);
			j++;
		}
		i++;
	}
}

void	draw_rays(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < vars->coll_count)
	{
		debug_point(&vars->debug.image, vars->collisions[i].pos);
		ft_draw_line(&vars->debug,
			ft_vec2_mul(vars->player.pos, TILE_SIZE),
			ft_vec2_mul(vars->collisions[i].pos, TILE_SIZE), g_yellow);
		i++;
	}
}

void	draw_player(t_vars *vars)
{
	t_player	player;
	t_input		inputs;
	t_vec2		move_dir;

	inputs = vars->inputs;
	player = vars->player;
	for (int i = (player.pos.x * TILE_SIZE) - PLAYER_RAD; i < (player.pos.x * TILE_SIZE) + PLAYER_RAD; i++)
		for (int j = (player.pos.y * TILE_SIZE) - PLAYER_RAD; j < (player.pos.y * TILE_SIZE) + PLAYER_RAD; j++)
			if((i >= 0 && i < WIDTH) && (j >= 0 && j < HEIGHT))
				ft_put_pixel(&vars->debug.image, i, j, g_green);
	ft_draw_line(&vars->debug, ft_vec2_mul(player.pos, TILE_SIZE),
		ft_vec2_mul(ft_vec2_add(player.pos, player.dir), TILE_SIZE), g_red);
	move_dir = ft_vec2_norm((t_vec2){.x = inputs.a_key + inputs.d_key,
			.y = inputs.w_key + inputs.s_key});
	move_dir = ft_vec2_rotate(move_dir,
			ft_rad_to_deg(-atan2(vars->player.dir.x, vars->player.dir.y)));
	move_dir = ft_vec2_inv(move_dir);
	ft_draw_line(&vars->debug, ft_vec2_mul(vars->player.pos, TILE_SIZE),
		ft_vec2_mul(ft_vec2_add(vars->player.pos, move_dir), TILE_SIZE),
		g_magenta);
}

void	debug_point(t_image *image, t_vec2 point)
{
	if (point.x < 0 && (point.x * TILE_SIZE) >= WIDTH)
		if (point.y < 0 && (point.y * TILE_SIZE) >= HEIGHT)
			return ;
	for (int i = (point.x * TILE_SIZE) - 2; i < (point.x * TILE_SIZE) + 2; i++)
		for (int j = (point.y * TILE_SIZE) - 2; j < (point.y * TILE_SIZE) + 2; j++)
			if((i >= 0 && i < WIDTH) && (j >= 0 && j < HEIGHT))
				ft_put_pixel(image, i, j, g_cyan);
}

void	update_debug(t_vars *vars)
{
	ft_fill_image(&vars->debug.win, &vars->debug.image, g_black);
	draw_map(vars);
	draw_rays(vars);
	draw_player(vars);
	mlx_put_image_to_window(vars->mlx.mlx, vars->debug.win.win,
		vars->debug.image.image, 0, 0);
}
