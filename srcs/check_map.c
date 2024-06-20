#include "../includes/cub3d.h"

void	check_r_map(t_vars *vars)
{
	int i;
	int j;

	i = 0;
	while (i < vars->height)
	{
		j = 0;
		while (j < vars->width)
		{
			if (vars->r_map[i][j] == '0' || vars->r_map[i][j] == 'N' || vars->r_map[i][j] == 'S'
			|| vars->r_map[i][j] == 'W' || vars->r_map[i][j] == 'E' )
			{
				if (i == 0 || i == vars->height - 1 || j == 0 || j == vars->width - 1)
				{
					printf("Error: Map is not closed.\n");
					exit(EXIT_FAILURE);
				}
				if (vars->r_map[i][j] == 'N' || vars->r_map[i][j] == 'S' || vars->r_map[i][j] == 'W' || vars->r_map[i][j] == 'E')
					vars->player_count++;
			}
			else if (vars->r_map[i][j] != '1' && vars->r_map[i][j] != '*')
			{
				printf("Error: Invalid character in the map.\n");
				exit(EXIT_FAILURE);
			}
			j++;
		}
		i++;
	}
	if (vars->player_count != 1)
	{
		printf("Error: Player start position not found in the map.\n");
		exit(EXIT_FAILURE);
	}
}