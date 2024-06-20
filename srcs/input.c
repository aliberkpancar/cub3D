#include "../includes/cub3d.h"

void	move_player(t_vars *vars, float move_x, float move_y)
{
	int	new_x;
	int	new_y;

    new_x = (int)(vars->pos_x + move_x);
    new_y = (int)(vars->pos_y + move_y);
    printf("Attempting to move to: new_x=%d, new_y=%d\n", new_x, new_y);
	if (new_x >= 0 && new_x < vars->temp_width && new_y >= 0 && new_y < vars->temp_height)
	{
		if (vars->temp_map[new_y][new_x] != '1')
		{
			vars->pos_x += move_x;
			vars->pos_y += move_y;
		}
	}
	else
		printf("Attempted move out of bounds to: new_x=%d, new_y=%d\n", new_x, new_y);
}

void rotate_player(t_player *player, float angle)
{
	float	old_dir_x;
	float	old_plane_x;

	old_dir_x = player->dir_x;
	old_plane_x = player->plane_x;
	player->dir_x = player->dir_x * cos(angle) - player->dir_y * sin(angle);
	player->dir_x = old_dir_x * sin(angle) + player->dir_y * cos(angle);
	player->plane_x = player->plane_x * cos(angle) - player->plane_y * sin(angle);
	player->plane_y = old_plane_x * sin(angle) + player->plane_y * cos(angle);
}

int	handle_input(int keycode, t_vars *vars)
{
	
	printf("Keycode:%d\n", keycode);
	if (keycode == 53)// ESC key
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	if (keycode == 13)// W key
		move_player(vars, vars->player.dir_x * MOVE_SPEED, vars->player.dir_y * MOVE_SPEED);
	if (keycode == 1)// S key
		move_player(vars, -vars->player.dir_x * MOVE_SPEED, -vars->player.dir_y * MOVE_SPEED);
	if (keycode == 0)// A key
		move_player(vars, vars->player.plane_x * -MOVE_SPEED, vars->player.plane_y * -MOVE_SPEED);
	if (keycode == 2)// D key
		move_player(vars, vars->player.plane_x * MOVE_SPEED, vars->player.plane_y * MOVE_SPEED);
	if (keycode == 123)// Left arrow key
		rotate_player(&vars->player, ROTATE_SPEED);
	if (keycode == 124)// Right arrow key
		rotate_player(&vars->player, -ROTATE_SPEED);
	render_scene(vars);
	return (0);
}
