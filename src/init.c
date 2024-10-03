#include "cub3d.h"

static void	allocate_t_map(t_vars *vars)
{
	int	i;

	vars->t_map = (char **)malloc(vars->temp_height * sizeof(char *));
	if (!vars->t_map)
	{
		printf("Error\n");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < vars->temp_height)
	{
		vars->t_map[i] = (char *)malloc((vars->temp_width + 1) * sizeof(char));
		if (!vars->t_map[i])
		{
			printf("Error\n");
			while (--i >= 0)
				free(vars->t_map[i]);
			free(vars->t_map);
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

static void	init_variables(t_vars *vars, char *map)
{
	vars->moves = (t_moves){0};
	vars->mlx.mlx = mlx_init();
	vars->ceiling = (t_color){0};
	vars->floor = (t_color){0};
	vars->player.pos.x = 4.5;
	vars->player.pos.y = 5.5;
	vars->player.dir.x = 0.0;
	vars->player.dir.y = 1.0;
	vars->player_count = 0;
	get_dimensions(vars, map);
	allocate_t_map(vars);
	vars->texture.east = NULL;
	vars->texture.west = NULL;
	vars->texture.north = NULL;
	vars->texture.south = NULL;
}

static void	allocate_map_tiles(t_vars *vars)
{
	vars->map.tiles = malloc(sizeof (char)
			* vars->map.size.x * vars->map.size.y);
	if (!vars->map.tiles)
	{
		printf("Error\n");
		free_t_map(vars);
		free_r_map(vars);
		free_textures(vars);
		exit(EXIT_FAILURE);
	}
}

static void	get_map(t_vars *vars)
{
	int	i;
	int	j;

	i = 0;
	vars->map.size.x = vars->width;
	vars->map.size.y = vars->height;
	allocate_map_tiles(vars);
	j = 0;
	while (j < vars->height - 2)
	{
		i = -1;
		while (++i < vars->width)
			if (vars->t_map[j][i] == '1' || vars->t_map[j][i] == '0'
				|| vars->t_map[j][i] == 'N' || vars->t_map[j][i] == 'S'
				|| vars->t_map[j][i] == 'W' || vars->t_map[j][i] == 'E')
				vars->map.tiles[j * vars->width + i] = vars->t_map[j][i];
		j++;
	}
	vars->map.tiles[j * vars->width + i] = '\0';
}

void	init_game(t_vars *vars, char *map)
{
	int	fd;

	fd = open(map, O_RDONLY);
	close(fd);
	init_variables(vars, map);
	parse_map(vars, map);
	init_player(vars);
	vars->player.move_speed = 10;
	vars->player.camera_speed = 100;
	create_r_map(vars);
	check_r_map(vars);
	init_textures(vars);
	init_win(vars);
	get_map(vars);
	mlx_put_image_to_window(vars->mlx.mlx, vars->mlx.win.win,
		vars->mlx.image.image, 0, 0);
	mlx_do_key_autorepeatoff(vars->mlx.mlx);
}
