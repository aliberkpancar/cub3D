#include "cub3d.h"

t_bool	ft_strchr_player(const char *s, int c)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(s);
	while (i <= len)
	{
		if (s[i] == (char)c)
			return (1);
		i++;
	}
	return (0);
}

void	get_player_positions(t_vars *vars)
{
	int		i;
	int		j;

	i = 0;
	while (i < vars->temp_height)
	{
		j = 0;
		while (j < vars->temp_width - 1)
		{
			if (ft_strchr_player("NSEW", vars->t_map[i][j]))
			{
					vars->player_count++;
					vars->player.pos.x = j + 0.5;
					vars->player.pos.y = i + 0.5;
			}
			j++;
		}
		i++;
	}
	if (vars->player_count != 1)
	{
		printf("Error\nInvalid player count\n");
		exit(EXIT_FAILURE);
	}
}
