#include "cub3d.h"

int	key_press_handler(int keycode, t_vars *vars)
{
	if (keycode == W_KEY)
		vars->inputs.w_key = -1;
	if (keycode == A_KEY)
		vars->inputs.a_key = -1;
	if (keycode == S_KEY)
		vars->inputs.s_key = 1;
	if (keycode == D_KEY)
		vars->inputs.d_key = 1;
	if (keycode == LEFT_KEY)
		vars->inputs.left_key = -1;
	if (keycode == RIGHT_KEY)
		vars->inputs.right_key = 1;
	if (keycode == ESC_KEY)
		exit(EXIT_SUCCESS);
	return (0);
}

int	key_release_handler(int keycode, t_vars *vars)
{
	if (keycode == W_KEY)
		vars->inputs.w_key = 0;
	if (keycode == A_KEY)
		vars->inputs.a_key = 0;
	if (keycode == S_KEY)
		vars->inputs.s_key = 0;
	if (keycode == D_KEY)
		vars->inputs.d_key = 0;
	if (keycode == LEFT_KEY)
		vars->inputs.left_key = 0;
	if (keycode == RIGHT_KEY)
		vars->inputs.right_key = 0;
	return (0);
}

void	player_collision(t_vars *vars, t_vec2 next_pos)
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
		if (vars->map.tiles[(int)vars->player.pos.x
				+ ((int)(next_pos.y + PLAYER_SIZE) * vars->map.size.x)] != '1')
			vars->player.pos.y = next_pos.y;
	}
	else
	{
		if (vars->map.tiles[(int)vars->player.pos.x
				+ ((int)(next_pos.y - PLAYER_SIZE) * vars->map.size.x)] != '1')
			vars->player.pos.y = next_pos.y;
	}
}

void	player_movement(t_vars *vars, t_vec2 dir)
{
	t_vec2		next_pos;

	next_pos = ft_vec2_add(vars->player.pos,
			ft_vec2_mul(dir, vars->player.move_speed * vars->delta_time));
	player_collision(vars, next_pos);
}

void	player_camera(t_vars *vars, t_bool rotate_dir)
{
	vars->player.dir = ft_vec2_rotate(vars->player.dir,
			vars->player.camera_speed * rotate_dir * vars->delta_time);
}
