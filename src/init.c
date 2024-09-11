#include "cub3d.h"

static void	init_player(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < vars->temp_height)
	{
		int j = 0;
		while (j < vars->temp_width)
		{
			if (vars->t_map[i][j] == 'N' || vars->t_map[i][j] == 'S' || vars->t_map[i][j] == 'W' || vars->t_map[i][j] == 'E')
			{
				if (vars->t_map[i][j] == 'N')
				{
					vars->player.dir.x = 0.0;
					vars->player.dir.y = -1.0;
				}
				else if (vars->t_map[i][j] == 'S')
				{
					vars->player.dir.x = 0.0;
					vars->player.dir.y = 1.0;
				}
				else if (vars->t_map[i][j] == 'W')
				{
					vars->player.dir.x = -1.0;
					vars->player.dir.y = 0.0;
				}
				else if (vars->t_map[i][j] == 'E')
				{
					vars->player.dir.x = 1.0;
					vars->player.dir.y = 0.0;
				}
			}
			j++;
		}
		i++;
	}
	vars->player.move_speed = 10;
	vars->player.camera_speed = 100;
}

static void	init_tex(t_vars *vars, t_image *tex, char *path)
{
	tex->line_count = vars->height - 2;
	tex->size_line = vars->width - 1;
	tex->image = mlx_xpm_file_to_image(vars->mlx.mlx, path,
			&tex->size_line, &tex->line_count);
	if (!tex->image) //free everything
		exit(EXIT_FAILURE); // handle error
	tex->data = (t_color *)mlx_get_data_addr(tex->image, &tex->bits_per_pixel,
			&tex->size_line, &tex->endian);
	if (!tex->data) //free everything
		exit(EXIT_FAILURE); // handle error
	tex->size_line /= (tex->bits_per_pixel / 8);
	rotate_index(tex);
}

void	init_win(t_vars *vars)
{
	if (vars->mlx.mlx == NULL)
		exit(EXIT_FAILURE);
	vars->mlx.win.height = HEIGHT;
	vars->mlx.win.width = WIDTH;
	vars->mlx.win.win = mlx_new_window(vars->mlx.mlx,
			WIDTH, HEIGHT, "cub3D");
	if (vars->mlx.win.win == NULL)
		exit(EXIT_FAILURE);
	vars->mlx.image.image = mlx_new_image(vars->mlx.mlx,
			vars->mlx.win.width, vars->mlx.win.height);
	vars->mlx.image.data = (t_color *)mlx_get_data_addr(vars->mlx.image.image,
			&vars->mlx.image.bits_per_pixel,
			&vars->mlx.image.size_line, &vars->mlx.image.endian);
	vars->mlx.image.size_line /= 4;
}

void	init_textures(t_vars *vars)
{
	//check xpm is empty or changable
	init_tex(vars, &vars->tex_south, vars->texture.north);
	init_tex(vars, &vars->tex_west, vars->texture.south);
	init_tex(vars, &vars->tex_north, vars->texture.west);
	init_tex(vars, &vars->tex_east, vars->texture.east);
	mirror_tex(&vars->tex_north);
	mirror_tex(&vars->tex_east);
}

static void	allocate_t_map(t_vars *vars)
{
	int i;

	vars->t_map = (char **)malloc(vars->temp_height * sizeof(char *)); 
	if (!vars->t_map)
	{
		printf("Error\n"); // free everything
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < vars->temp_height)
	{
		vars->t_map[i] = (char *)malloc((vars->temp_width + 1) * sizeof(char)); 
		if (!vars->t_map[i])
		{
			printf("Error\n"); // free everything
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

static void	init_variables(t_vars *vars, char *map)
{
	vars->inputs = (t_input){0};
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
}

static void	get_map(t_vars *vars)
{
	int i;
	int j;

	i = 0;
	vars->map.size.x = vars->width;
	vars->map.size.y = vars->height;
	vars->map.tiles = malloc(sizeof (char)
			* vars->map.size.x * vars->map.size.y);
	if (!vars->map.tiles)
	{
		printf("Error\n"); // free everything
		exit(EXIT_FAILURE);
	}
	j = 0;
	while (j < vars->height - 2)
	{
		i = 0;
		while (i < vars->width)
		{
			if (vars->t_map[j][i] == '1' || vars->t_map[j][i] == '0' || vars->t_map[j][i] == 'N' || vars->t_map[j][i] == 'S' || vars->t_map[j][i] == 'W' || vars->t_map[j][i] == 'E')
				vars->map.tiles[j * vars->width + i] = vars->t_map[j][i];
			i++;
		}
		j++;
	}
	vars->map.tiles[j * vars->width + i] = '\0';
}

void	init_game(t_vars *vars, char *map)
{	
	init_variables(vars, map);
	parse_map(vars, map);
	init_player(vars);
	create_r_map(vars);
	check_r_map(vars);
	init_textures(vars);
	init_win(vars);
	get_map(vars);
	mlx_put_image_to_window(vars->mlx.mlx, vars->mlx.win.win,
		vars->mlx.image.image, 0, 0);
	mlx_do_key_autorepeatoff(vars->mlx.mlx);
}
