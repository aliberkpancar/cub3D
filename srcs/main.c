#include "../includes/cub3d.h"
#include "../mlx/mlx.h"

static void	init_var(t_vars *vars, char *map)
{
	int i;

	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	vars->image.image = mlx_new_image(vars->mlx, WIN_WIDTH, WIN_HEIGHT);
	vars->image.addr = mlx_get_data_addr(vars->image.image, &vars->image.bits_per_pixel, &vars->image.line_length, &vars->image.endian);
	vars->pos_x = 22.0;
    vars->pos_y = 12.0;
    vars->dir_x = -1.0;
    vars->dir_y = 0.0;
    vars->plane_x = 0.0;
    vars->plane_y = 0.66;
	vars->map_width = 0;
	vars->map_height = 0;
	get_dimensions(vars, map);
	printf("Dimensions w: %d - h: %d\n", vars->map_width, vars->map_height);
	vars->map = (char **)malloc(sizeof(char *) * vars->map_height);
	if (!vars->map)
	{
		printf("Error\n");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < vars->map_height)
	{
		vars->map[i] = (char *)malloc(sizeof(char) * vars->map_width + 1);
		if (!vars->map[i])
		{
			printf("Error\n");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	vars->ray.side_dist_x = 0;
    vars->ray.side_dist_y = 0;
    vars->ray.delta_dist_x = 0;
    vars->ray.delta_dist_y = 0;
    vars->ray.map_x = 0;
    vars->ray.map_y = 0;
    vars->ray.step_x = 0;
    vars->ray.step_y = 0;
    vars->ray.side = 0;
}

static void init_player_pos(t_vars *vars)
{
	int x;
	int y;

	y = 0;
	while (y < vars->map_height)
	{
		x = 0;
		while (x < vars->map_width)
		{
			if (vars->map[y][x] == 'N' || vars->map[y][x] == 'S' || vars->map[y][x] == 'W' || vars->map[y][x] == 'E')
			{
				vars->pos_x = x + 0.5;
				vars->pos_y = y + 0.5;
				if (vars->map[y][x] == 'N')
				{
					vars->dir_x = 0;
					vars->dir_y = -1;
					vars->plane_x = 0.66;
					vars->plane_y = 0;
				}
				else if (vars->map[y][x] == 'S')
				{
					vars->dir_x = 0;
					vars->dir_y = 1;
					vars->plane_x = -0.66;
					vars->plane_y = 0;
				}
				else if (vars->map[y][x] == 'W')
				{
					vars->dir_x = -1;
					vars->dir_y = 0;
					vars->plane_x = 0;
					vars->plane_y = -0.66;
				}
				else if (vars->map[y][x] == 'E')
				{
					vars->dir_x = 1;
					vars->dir_y = 0;
					vars->plane_x = 0;
					vars->plane_y = 0.66;
				}
				vars->map[y][x] = '0';
				return ;
			}
			x++;
		}
		y++;
	}
    printf("Error: Player start position not found in the map.\n");
    exit(EXIT_FAILURE);
}

int main(int argc, char **argv)
{
	t_vars *vars;

	if (argc != 2)
		return (printf("Error\n"), 1); // check printf is allowed
	vars = (t_vars *)malloc(sizeof(t_vars));
	if (!vars)
	{
		printf("Error\n");
		exit(EXIT_FAILURE);
	}
	init_var(vars, argv[1]);
	// texture_init(vars);
	parse_map(argv[1], vars);
	printf("Map parsed\n");
	init_player_pos(vars);
	mlx_loop_hook(vars->mlx, (int (*)(void *))main_loop, &vars);
	// for (int x = 0; x < WIN_WIDTH; x++) {
    // double camera_x = 2 * x / (double)WIN_WIDTH - 1;
    // vars.ray.ray_dir_x = vars.dir_x + vars.plane_x * camera_x;
    // vars.ray.ray_dir_y = vars.dir_y + vars.plane_y * camera_x;
    // printf("Ray %d: dir_x: %f, dir_y: %f\n", x, vars.ray.ray_dir_x, vars.ray.ray_dir_y);
	// }
	mlx_hook(vars->win, 2, 1L<<0, handle_input, &vars);
	mlx_loop(vars->mlx);
	return (0);
}
