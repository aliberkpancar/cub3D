#include "cub3d.h"

void	ft_draw_circle(t_mlx *mlx, int center_x, int center_y, int radius, int color)
{
	int	x;
	int	y;
	int	sq_radius;

	sq_radius = radius * radius;
	y = -radius;
	while (y <= radius)
	{
		x = -radius;
		while (x <= radius)
		{
			if (x * x + y * y <= sq_radius)
				mlx_pixel_put(mlx->mlx, mlx->win.win, center_x + x, center_y + y, color);
			x++;
		}
		y++;
	}
}

void	ft_draw_rect(t_mlx *mlx, int x, int y, int width, int height, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			mlx_pixel_put(mlx->mlx, mlx->win.win, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

void	ft_draw_line(t_mlx *mlx, t_vec pt1, t_vec pt2, t_color color)
{
	int	steps;
	int	i;
	float	x_inc;
	float	y_inc;
	float	x;
	float	y;

	steps = fabs(pt2.x - pt1.x) > fabs(pt2.y - pt1.y) ? fabs((pt2.x - pt1.x)) : fabs(pt2.y - pt1.y);
	x_inc = (pt2.x - pt1.x) / (float)steps;
	y_inc = (pt2.y - pt1.y) / (float)steps;
	x = pt1.x;
	y = pt1.y;
	i = 0;
	while (i <= steps)
	{
		mlx_pixel_put(mlx->mlx, mlx->win.win, (int)x, (int)y, color.value);
		x += x_inc;
		y += y_inc;
		i++;
	}
}


void	ft_draw_triangle(t_mlx *mlx, int center_x, int center_y, int size, float direction, int color)
{
	t_vec pt1 = {{center_x + cos(direction) * size, center_y + sin(direction) * size}};
	t_vec pt2 = {{center_x + cos(direction + M_PI / 6) * size / 1.5, center_y + sin(direction + M_PI / 6) * size / 1.5}};
	t_vec pt3 = {{center_x + cos(direction - M_PI / 6) * size / 1.5, center_y + sin(direction - M_PI / 6) * size / 1.5}};
	t_color color_vec;
	color_vec.value = color;
	ft_draw_line(mlx, pt1, pt2, color_vec);
	ft_draw_line(mlx, pt2, pt3, color_vec);
	ft_draw_line(mlx, pt3, pt1, color_vec);
}


void	draw_minimap(t_vars *vars)
{
	int	x;
	int	y;
	int tile_size = 10;
	int player_minimap_x;
	int player_minimap_y;

	y = 0;
	while (y < vars->map.size.y)
	{
		x = 0;
		while (x < vars->map.size.x)
		{
			ft_draw_rect(&vars->mlx, x * tile_size, y * tile_size, tile_size, tile_size, 0x97000000);
			x++;
		}
		y++;
	}
	y = 0;
	while (y < vars->map.size.y)
	{
		x = 0;
		while (x < vars->map.size.x)
		{
			if (vars->map.tiles[y * vars->map.size.x + x] == '1')
				ft_draw_rect(&vars->mlx, x * tile_size, y * tile_size, tile_size, tile_size, 0xFFFFFF);
			x++;
		}
		y++;
	}
	
	player_minimap_x = vars->player.pos.x * tile_size;
	player_minimap_y = vars->player.pos.y * tile_size;
	ft_draw_circle(&vars->mlx, player_minimap_x, player_minimap_y, PLAYER_RAD, 0xFF0000);
	ft_draw_triangle(&vars->mlx, player_minimap_x, player_minimap_y, 20, atan2(vars->player.dir.y, vars->player.dir.x), 0x00FF00);
}