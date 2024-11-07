/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apancar <apancar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:15:37 by apancar           #+#    #+#             */
/*   Updated: 2024/11/07 11:48:16 by apancar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_press_handler(int keycode, t_vars *vars)
{
	if (keycode == W_KEY)
		vars->moves.w_key = -1;
	if (keycode == A_KEY)
		vars->moves.a_key = -1;
	if (keycode == S_KEY)
		vars->moves.s_key = 1;
	if (keycode == D_KEY)
		vars->moves.d_key = 1;
	if (keycode == LEFT_KEY)
		vars->moves.left_key = -1;
	if (keycode == RIGHT_KEY)
		vars->moves.right_key = 1;
	if (keycode == ESC_KEY)
		exit(EXIT_SUCCESS);
	return (0);
}

int	key_release_handler(int keycode, t_vars *vars)
{
	if (keycode == W_KEY)
		vars->moves.w_key = 0;
	if (keycode == A_KEY)
		vars->moves.a_key = 0;
	if (keycode == S_KEY)
		vars->moves.s_key = 0;
	if (keycode == D_KEY)
		vars->moves.d_key = 0;
	if (keycode == LEFT_KEY)
		vars->moves.left_key = 0;
	if (keycode == RIGHT_KEY)
		vars->moves.right_key = 0;
	return (0);
}

void	player_collision(t_vars *vars, t_vec next_pos)
{
	if (next_pos.x > vars->player.pos.x)
	{
		if (vars->map.tiles[(int)(next_pos.x + PLAYER_SIZE)
			+ ((int)vars->player.pos.y * vars->map.size.x)] != '1')
			vars->player.pos.x = next_pos.x;
	}
	else
	{
		if (vars->map.tiles[(int)(next_pos.x - PLAYER_SIZE)
			+ ((int)vars->player.pos.y * vars->map.size.x)] != '1')
			vars->player.pos.x = next_pos.x;
	}
	if (next_pos.y > vars->player.pos.y)
	{
		if (vars->map.tiles[(int)vars->player.pos.x \
		+ (((int)(next_pos.y + PLAYER_SIZE)) * vars->map.size.x)] != '1')
			vars->player.pos.y = next_pos.y;
	}
	else
	{
		if (vars->map.tiles[(int)vars->player.pos.x \
		+ (((int)(next_pos.y - PLAYER_SIZE)) * vars->map.size.x)] != '1')
			vars->player.pos.y = next_pos.y;
	}
}

void	player_movement(t_vars *vars, t_vec dir)
{
	t_vec		next_pos;

	next_pos = ft_vec_add(vars->player.pos,
			ft_vec_mul(dir, vars->player.move_speed));
	player_collision(vars, next_pos);
}

void	player_camera(t_vars *vars, t_bool rotate_dir)
{
	vars->player.dir = ft_vec_rotate(vars->player.dir,
			vars->player.camera_speed * rotate_dir);
}
