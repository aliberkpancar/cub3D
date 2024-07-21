#include "cub3d.h"

static void	ft_set_direction(t_vars *vars, char c)
{
	if (c == 'N')
	{
		vars->ray.dir.x = -1;
		vars->ray.dir.y = 0;
	}
	else if (c == 'S')
	{
		vars->ray.dir.x = 1;
		vars->ray.dir.y = 0;
	}
	else if (c == 'W')
	{
		vars->ray.dir.x = 0;
		vars->ray.dir.y = -1;
	}
	else if (c == 'E')
	{
		vars->ray.dir.x = 0;
		vars->ray.dir.y = 1;
	}
}

// static void	ft_set_plane(t_vars *vars, char c)
// {
// 	if (c == 'N')
// 	{
// 		vars->ray.plane.x = 0;
// 		vars->ray.plane.y = 0.66;
// 	}
// 	else if (c == 'S')
// 	{
// 		vars->ray.plane.x = 0;
// 		vars->ray.plane.y = -0.66;
// 	}
// 	else if (c == 'W')
// 	{
// 		vars->ray.plane.x = -0.66;
// 		vars->ray.plane.y = 0;
// 	}
// 	else if (c == 'E')
// 	{
// 		vars->ray.plane.x = 0.66;
// 		vars->ray.plane.y = 0;
// 	}
// }

static void	ft_get_direction(t_vars *vars, char c)
{
	ft_set_direction(vars, c);
	// ft_set_plane(vars, c);
}

void	get_player_positions(t_vars *vars)
{
	int		i;
	int		j;

	i = 0;
	while (i < vars->height)
	{
		j = 0;
		while (j < vars->width)
		{
			if (ft_strchr("NSEW", vars->r_map[i][j]))
			{
					vars->player_count++;
					vars->player.pos.x = j + 0.5;
					vars->player.pos.y = i + 0.5;
					ft_get_direction(vars, vars->r_map[i][j]);
			}
			j++;
		}
		i++;
	}
}
