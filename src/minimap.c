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
			ft_draw_rect(&vars->mlx, x * tile_size, y * tile_size, tile_size, tile_size, 0x000000);
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
	ft_draw_circle(&vars->mlx, player_minimap_x, player_minimap_y, PLAYER_RAD, 0xFF0000); // Kırmızı renkli oyuncu noktası
}