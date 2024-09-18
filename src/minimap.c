#include "cub3d.h"

void	ft_draw_triangle(t_mlx *mlx, int *center, float direction, int color)
{
	t_color	color_vec;
	t_vec	pt1;
	t_vec	pt2;
	t_vec	pt3;

	pt1 = set_vals(center[0] + cos(direction)
			* 20, center[1] + sin(direction) * 20);
	pt2 = set_vals(center[0] + cos(direction + M_PI / 6)
			* 20 / 1.5, center[1] + sin(direction + M_PI / 6) * 20 / 1.5);
	pt3 = set_vals(center[0] + cos(direction - M_PI / 6)
			* 20 / 1.5, center[1] + sin(direction - M_PI / 6) * 20 / 1.5);
	color_vec.value = color;
	ft_draw_line(mlx, pt1, pt2, color_vec);
	ft_draw_line(mlx, pt2, pt3, color_vec);
	ft_draw_line(mlx, pt3, pt1, color_vec);
}

void	draw2(t_vars *vars)
{
	int	*player_minimap;

	player_minimap = malloc(sizeof(int) * 2);
	player_minimap[0] = vars->player.pos.x * 10;
	player_minimap[1] = vars->player.pos.y * 10;
	ft_draw_circle(&vars->mlx, player_minimap, PLAYER_RAD, 0xFF0000);
	ft_draw_triangle(&vars->mlx, player_minimap,
		atan2(vars->player.dir.y, vars->player.dir.x), 0x00FF00);
}

static void	draw_bg(t_vars *vars)
{
	int	x;
	int	y;

	y = 0;
	while (y < vars->map.size.y)
	{
		x = 0;
		while (x < vars->map.size.x)
		{
			ft_draw_rect(&vars->mlx, x * 10, y
				* 10, 0x97000000);
			x++;
		}
		y++;
	}
}

void	draw_minimap(t_vars *vars)
{
	int	x;
	int	y;

	draw_bg(vars);
	y = 0;
	while (y < vars->map.size.y)
	{
		x = 0;
		while (x < vars->map.size.x)
		{
			if (vars->map.tiles[y * vars->map.size.x + x] == '1')
				ft_draw_rect(&vars->mlx, x * 10, y
					* 10, 0xFFFFFF);
			x++;
		}
		y++;
	}
	draw2(vars);
}
