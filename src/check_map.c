#include "cub3d.h"

static void	check_char(char c)
{
	if (c != 'N' && c != 'S' && c != 'W' && c != 'E' && c != '1' &&
		c != '*' && c != 'B' && c != '0' && c != ' ' && c != '\t' &&
		c != '\n' && c != '\0')
	{
		printf("Error\nInvalid character in the map: %c\n", c);
		exit(EXIT_FAILURE);
	}
}

void	check_r_map(t_vars *vars)
{
	int	i;
	int	j;

	vars->player_count = 0;
	get_player_positions(vars);
	if (vars->player_count != 1)
	{
		printf("Error\nInvalid player count\n");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < vars->height)
	{
		j = 0;
		while (j < vars->width)
		{
			check_char(vars->r_map[i][j]);
			j++;
		}
		i++;
	}
	
}
