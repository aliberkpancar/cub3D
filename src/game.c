/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliberk <aliberk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:15:58 by apancar           #+#    #+#             */
/*   Updated: 2024/10/21 06:30:41 by aliberk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	raycast(t_vars *vars, t_vec start, t_vec dir, t_hit *hit)
{
	t_vec	vertical;
	t_vec	horizontal;
	float	dist_vertical;
	float	dist_horizontal;

	dist_vertical = 0;
	dist_horizontal = 0;
	vertical = hit_vertical(vars, start, dir, &dist_vertical);
	horizontal = hit_horizontal(vars, start, dir, &dist_horizontal);
	if (dist_horizontal <= dist_vertical)
	{
		hit->pos = horizontal;
		if ((start.y - horizontal.y) < 0)
			hit->face = north;
		else
			hit->face = south;
	}
	else
	{
		hit->pos = vertical;
		if ((start.x - vertical.x) < 0)
			hit->face = west;
		else
			hit->face = east;
	}
}

static void	update_rays(t_vars *vars)
{
	int		i;
	float	degree;

	degree = -(WIDTH / 2);
	vars->num_of_rays = WIDTH;
	i = 0;
	while (i < WIDTH)
	{
		vars->ray_angle[i] = ft_rad_to_deg(atan(degree / WIDTH));
		raycast(vars, vars->player.pos,
			ft_vec_rotate(vars->player.dir, vars->ray_angle[i]),
			&vars->collisions[i]);
		degree += 1;
		i++;
	}
}

void	update_player(t_vars *vars)
{
	t_vec	move_dir;
	t_bool	rotate_dir;
	t_moves	moves;

	moves = vars->moves;
	move_dir = (t_vec){.x = moves.a_key + moves.d_key,
		.y = moves.w_key + moves.s_key};
	move_dir = ft_vec_norm(move_dir);
	move_dir = ft_vec_rotate(move_dir,
			ft_rad_to_deg(-atan2(vars->player.dir.x, vars->player.dir.y)));
	move_dir = ft_vec_inversion(move_dir);
	rotate_dir = moves.left_key + moves.right_key;
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
	draw_minimap(vars);
	frame_rate = ft_itoa((int)(1 / vars->delta_time));
	mlx_string_put(vars->mlx.mlx, vars->mlx.win.win, HEIGHT, WIDTH,
		0x00ff00ff, frame_rate);
	free(frame_rate);
	return (0);
}
