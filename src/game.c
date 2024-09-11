#include "cub3d.h"

static void	update_rays(t_vars *vars)
{
	int		i;
	float	degree;

	vars->collission_count = WIDTH;
	// vars->collisions = ft_calloc(vars->collission_count, sizeof (t_hit));
	// if (!vars->collisions)
	// 	exit(EXIT_FAILURE);
	// vars->collision_degree = ft_calloc(vars->collission_count, sizeof (float));
	// if (vars->collision_degree == NULL)
	// 	exit(EXIT_FAILURE);
	degree = -(WIDTH / 2);
	i = 0;
	while (i < WIDTH)
	{
		vars->collision_degree[i] = ft_rad_to_deg(atan(degree / WIDTH));
 		raycast(vars, vars->player.pos,
			ft_vec_rotate(vars->player.dir, vars->collision_degree[i]),
			&vars->collisions[i]);
		degree += 1;
		i++;
	}
}

void	update_player(t_vars *vars)
{
	t_vec	move_dir;
	t_bool	rotate_dir;
	t_input	inputs;

	inputs = vars->inputs;
	move_dir = (t_vec){.x = inputs.a_key + inputs.d_key,
		.y = inputs.w_key + inputs.s_key};
	move_dir = ft_vec_norm(move_dir);
	move_dir = ft_vec_rotate(move_dir,
			ft_rad_to_deg(-atan2(vars->player.dir.x, vars->player.dir.y)));
	move_dir = ft_vec_inversion(move_dir); //why we invert negative these directories?
	rotate_dir = inputs.left_key + inputs.right_key;
	player_camera(vars, rotate_dir);
	player_movement(vars, move_dir);
}

int	game(void *param)
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
	draw_background(vars);
	draw_walls(vars);
	mlx_put_image_to_window(vars->mlx.mlx, vars->mlx.win.win,
		vars->mlx.image.image, 0, 0);
	frame_rate = ft_itoa((int)(1 / vars->delta_time));
	mlx_string_put(vars->mlx.mlx, vars->mlx.win.win, HEIGHT, WIDTH, g_magenta.value,
		frame_rate);
	draw_minimap(vars);
	free(frame_rate);
	return (0);
}
