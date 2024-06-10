// static void	render_background(t_vars *vars)
// {
// 	int	x;
// 	int	y;
// 	t_color	black;

// 	black = (t_color){0, 0, 0};
// 	y = 0;
// 	while (y < WIN_HEIGHT)
// 	{
// 		x = 0;
// 		while (x < WIN_WIDTH)
// 		{
// 			my_mlx_pixel_put(&vars->image, x, y, black);
// 			x++;
// 		}
// 		y++;
// 	}
// }

// static void	render_ceiling_floors(t_vars *vars)
// {
// 	int	x;
// 	int	y;

// 	y = 0;
// 	while (y < WIN_HEIGHT / 2)
// 	{
// 		x = 0;
// 		while (x < WIN_WIDTH)
// 		{
// 			my_mlx_pixel_put(&vars->image, x, y, vars->ceiling);
// 			x++;
// 		}
// 		y++;
// 	}
// 	while (y < WIN_HEIGHT)
// 	{
// 		x = 0;
// 		while (x < WIN_WIDTH)
// 		{
// 			my_mlx_pixel_put(&vars->image, x, y, vars->floor);
// 			x++;
// 		}
// 		y++;
// 	}
// }

// static void	ray_position_and_direction(t_vars *vars, int x)
// {
// 	double	camera_x;

// 	camera_x = 2 * x / (double)WIN_WIDTH - 1;
// 	vars->ray.ray_dir_x = vars->dir_x + vars->plane_x * camera_x;
// 	vars->ray.ray_dir_y = vars->dir_y + vars->plane_y * camera_x;
// }

// static void	initial_map_position(t_vars *vars)
// {
// 	vars->ray.map_x = (int)vars->pos_x;
// 	vars->ray.map_y = (int)vars->pos_y;
// }

// static void	calculate_deltas(t_vars *vars)
// {
// 	vars->ray.delta_dist_x = fabs(1 / vars->ray.ray_dir_x);
// 	vars->ray.delta_dist_y = fabs(1 / vars->ray.ray_dir_y);
// }

// static void	init_step_and_sidedist(t_vars *vars)
// {
// 	if (vars->ray.ray_dir_x < 0)
// 	{
// 		vars->ray.step_x = -1;
// 		vars->ray.side_dist_x = (vars->pos_x - vars->ray.map_x) * vars->ray.delta_dist_x;
// 	}
// 	else
// 	{
// 		vars->ray.step_x = 1;
// 		vars->ray.side_dist_x = (vars->ray.map_x + 1.0 - vars->pos_x) * vars->ray.delta_dist_x;
// 	}
// 	if (vars->ray.ray_dir_y < 0)
// 	{
// 		vars->ray.step_y = -1;
// 		vars->ray.side_dist_y = (vars->pos_y - vars->ray.map_y) * vars->ray.delta_dist_y;
// 	}
// 	else
// 	{
// 		vars->ray.step_y = 1;
// 		vars->ray.side_dist_y = (vars->ray.map_y + 1.0 - vars->pos_y) * vars->ray.delta_dist_y;
// 	}
// }

// static void	dda_algorithm(t_vars *vars)
// {
// 	int	hit;

// 	hit = 0;
// 	while (hit == 0)
// 	{
// 		if (vars->ray.side_dist_x < vars->ray.side_dist_y)
// 		{
// 			vars->ray.side_dist_x += vars->ray.delta_dist_x;
// 			vars->ray.map_x += vars->ray.step_x;
// 			vars->ray.side = 0;
// 		}
// 		else
// 		{
// 			vars->ray.side_dist_y += vars->ray.delta_dist_y;
// 			vars->ray.map_y += vars->ray.step_y;
// 			vars->ray.side = 1;
// 		}
// 		printf("map_x:%d map_y:%d\n", vars->ray.map_x, vars->ray.map_y);
// 		getchar();
// 		if (vars->map[vars->ray.map_x][vars->ray.map_y] == '1')
// 			hit = 1;
// 	}
// }

// static void	calculate_distance(t_vars *vars)
// {
// 	if (vars->ray.side == 0)
// 		vars->ray.perp_wall_dist = (vars->ray.map_x - vars->pos_x + (1 - vars->ray.step_x) / 2) / vars->ray.ray_dir_x;
// 	else
// 		vars->ray.perp_wall_dist = (vars->ray.map_y - vars->pos_y + (1 - vars->ray.step_y) / 2) / vars->ray.ray_dir_y;
// }

// static void render_walls(t_vars *vars)
// {
// 	int	x,y;

// 	x = 0;
// 	while (x < WIN_WIDTH)
// 	{
// 		ray_position_and_direction(vars, x);
// 		initial_map_position(vars);
// 		calculate_deltas(vars);
// 		init_step_and_sidedist(vars);
// 		dda_algorithm(vars);
// 		calculate_distance(vars);
// 		vars->ray.line_height = (int)(WIN_HEIGHT / vars->ray.perp_wall_dist);
// 		vars->ray.draw_start = -vars->ray.line_height / 2 + WIN_HEIGHT / 2;
// 		if (vars->ray.draw_start < 0)
// 			vars->ray.draw_start = 0;
// 		vars->ray.draw_end = vars->ray.line_height / 2 + WIN_HEIGHT / 2;
// 		if (vars->ray.draw_end >= WIN_HEIGHT)
// 			vars->ray.draw_end = WIN_HEIGHT - 1;
// 		y = vars->ray.draw_start;
// 		while (y < vars->ray.draw_end)
// 		{
// 			my_mlx_pixel_put_int(&vars->image, x, vars->ray.draw_start, 0x00FF00);
// 			y++;
// 		}
// 		x++;
// 	}
// }

// void render_scene(t_vars *vars)
// {
// 	render_background(vars);
// 	render_ceiling_floors(vars);
// 	render_walls(vars);
// }