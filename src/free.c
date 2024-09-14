#include "cub3d.h"

void	free_t_map(t_vars *vars)
{
	int	i;

	i = 0;
	while (vars->t_map[i])
	{
		free(vars->t_map[i]);
		i++;
	}
	free(vars->t_map);
}

void	free_r_map(t_vars *vars)
{
	int	i;

	i = 0;
	while (vars->r_map[i])
	{
		free(vars->r_map[i]);
		i++;
	}
	free(vars->r_map);
}

void	free_all(t_vars *vars)
{
	int i;

	i = 0;
	while (vars->t_map[i])
	{
		free(vars->t_map[i]);
		i++;
	}
	free(vars->t_map);
	i = 0;
	while (vars->r_map[i])
	{
		free(vars->r_map[i]);
		i++;
	}
	free(vars->r_map);
	free(vars->map.tiles);
}
