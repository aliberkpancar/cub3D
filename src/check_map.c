#include "cub3d.h"

static void	check_char(t_vars *vars, char c)
{
	if (c != 'N' && c != 'S' && c != 'W' && c != 'E' && c != '1'
		&& c != '*' && c != 'B' && c != '0' && c != ' ' && c != '\t'
		&& c != '\n' && c != '\0')
	{
		printf("Error\nInvalid character in the map: %c\n", c);
		free_t_map(vars);
		free_r_map(vars);
		exit(EXIT_FAILURE);
	}
}

static void	set_order(char **keys)
{
	keys[0] = "NO";
	keys[1] = "SO";
	keys[2] = "WE";
	keys[3] = "EA";
}

void	check_order(int fd)
{
	char	*tmp;
	char	*keys[4];
	int		i;

	set_order(keys);
	tmp = get_next_line(fd);
	i = 0;
	while (i < 4)
	{
		if (ft_strncmp(tmp, keys[i++], 2) == 0)
		{
			free(tmp);
			tmp = get_next_line(fd);
		}
		else
		{
			close(fd);
			free(tmp);
			printf("Error\nWrong order or type for textures\n");
			exit(EXIT_FAILURE);
		}
	}
	free(tmp);
}

void	check_r_map(t_vars *vars)
{
	int	i;
	int	j;

	get_player_positions(vars);
	i = 0;
	while (i < vars->height)
	{
		j = 0;
		while (j < vars->width)
		{
			check_char(vars, vars->r_map[i][j]);
			j++;
		}
		i++;
	}
}
