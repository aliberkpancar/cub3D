#include "cub3d.h"

static void	update_rays(t_vars *vars)
{
	int		i;
	float	degree;

	vars->coll_count = WIDTH;
	vars->collisions = ft_calloc(vars->coll_count, sizeof (t_hit));
	if (!vars->collisions)
		exit(EXIT_FAILURE);
	vars->coll_degree = ft_calloc(vars->coll_count, sizeof (float));
	if (vars->coll_degree == NULL)
		exit(EXIT_FAILURE);
	degree = -(WIDTH / 2);
	i = 0;
	while (i < WIDTH)
	{
		vars->coll_degree[i] = ft_rad_to_deg(atan(degree / WIDTH));
 		raycast(vars, vars->player.pos,
			ft_vec2_rotate(vars->player.dir, vars->coll_degree[i]),
			&vars->collisions[i]);
		degree += 1;
		i++;
	}
}

void	update_player(t_vars *vars)
{
	t_vec2	move_dir;
	t_bool	rotate_dir;
	t_input	inputs;

	inputs = vars->inputs;
	move_dir = (t_vec2){.x = inputs.a_key + inputs.d_key,
		.y = inputs.w_key + inputs.s_key};
	move_dir = ft_vec2_norm(move_dir);
	move_dir = ft_vec2_rotate(move_dir,
			ft_rad_to_deg(-atan2(vars->player.dir.x, vars->player.dir.y)));
	move_dir = ft_vec2_inv(move_dir); //why we invert negative these directories?
	// ft_draw_line(&vars->debug, ft_vec2_mul(vars->player.pos, TILE_SIZE),
	// 	ft_vec2_mul(ft_vec2_add(vars->player.pos, move_dir), TILE_SIZE),
	// 	g_magenta);
	rotate_dir = inputs.left_key + inputs.right_key;
	player_camera(vars, rotate_dir);
	player_movement(vars, move_dir);
}

int	update(void *param)
{
	static double	last_time = 0;
	double			curr_time;
	char			*frame_rate;
	t_vars			*vars;

	vars = (t_vars *)param;
	curr_time = clock();
	vars->delta_time = (double)(curr_time - last_time) / CLOCKS_PER_SEC;
	last_time = curr_time;
	update_player(vars);
	update_rays(vars);
	#if DEBUG == 1
	update_debug(vars);
	#endif
	draw_background(vars);
	draw_walls(vars);
	mlx_put_image_to_window(vars->mlx.mlx, vars->mlx.win.win,
		vars->mlx.image.image, 0, 0);
	frame_rate = ft_itoa((int)(1 / vars->delta_time));
	mlx_string_put(vars->mlx.mlx, vars->mlx.win.win, HEIGHT, WIDTH, g_magenta.value,
		frame_rate);
	free(frame_rate);
	free(vars->collisions);
	free(vars->coll_degree);
	return (0);
}
