#include "cub3d.h"
#include "./mlx/mlx.h"
#include <math.h>

void	move_forward(t_camera *cam, char **map)
{
	if (map[(int)(cam->posX + cam->dirX * MOVE_SPEED)][(int)cam->posY] == '0')
		cam->posX += cam->dirX * MOVE_SPEED;
	if (map[(int)cam->posX][(int)(cam->posY + cam->dirY * MOVE_SPEED)] == '0')
		cam->posY += cam->dirY * MOVE_SPEED;
}

void	move_backward(t_camera *cam, char **map)
{
    if (map[(int)(cam->posX - cam->dirX * MOVE_SPEED)][(int)cam->posY] == '0')
        cam->posX -= cam->dirX * MOVE_SPEED;
    if (map[(int)cam->posX][(int)(cam->posY - cam->dirY * MOVE_SPEED)] == '0')
        cam->posY -= cam->dirY * MOVE_SPEED;
}

void rotate_left(t_camera *cam)
{
	double oldDirX = cam->dirX;
	cam->dirX = cam->dirX * cos(ROT_SPEED) - cam->dirY * sin(ROT_SPEED);
	cam->dirY = oldDirX * sin(ROT_SPEED) + cam->dirY * cos(ROT_SPEED);
	double oldPlaneX = cam->planeX;
	cam->planeX = cam->planeX * cos(ROT_SPEED) - cam->planeY * sin(ROT_SPEED);
	cam->planeY = oldPlaneX * sin(ROT_SPEED) + cam->planeY * cos(ROT_SPEED);
}

void rotate_right(t_camera *cam)
{
	double oldDirX = cam->dirX;
	cam->dirX = cam->dirX * cos(-ROT_SPEED) - cam->dirY * sin(-ROT_SPEED);
	cam->dirY = oldDirX * sin(-ROT_SPEED) + cam->dirY * cos(-ROT_SPEED);
	double oldPlaneX = cam->planeX;
	cam->planeX = cam->planeX * cos(-ROT_SPEED) - cam->planeY * sin(-ROT_SPEED);
	cam->planeY = oldPlaneX * sin(-ROT_SPEED) + cam->planeY * cos(-ROT_SPEED);
}

int	key_press(t_game *game, int keycode)
{
	if (keycode == 13) // W key
		move_forward(game->cam, game->map);
	if (keycode == 1) // S key
		move_backward(game->cam, game->map);
	if (keycode == 0) // A key
		rotate_left(game->cam);
	if (keycode == 2) // D key
		rotate_right(game->cam);
	// mlx_put_image_to_window(game->mlx, game->win, game->image, 0, 0);
	// Add other keys if needed
	return (0);
}