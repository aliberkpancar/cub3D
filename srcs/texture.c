#include "../mlx/mlx.h"
#include "../includes/cub3d.h"

void texture_init(t_vars *vars)
{
	vars->textures.north = NULL;
	vars->textures.south = NULL;
	vars->textures.west = NULL;
	vars->textures.east = NULL;
	vars->textures.north_image = NULL;
	vars->textures.south_image = NULL;
	vars->textures.west_image = NULL;
	vars->textures.east_image = NULL;
	vars->textures.north_width = 0;
	vars->textures.north_height = 0;
	vars->textures.south_width = 0;
	vars->textures.south_height = 0;
	vars->textures.west_width = 0;
	vars->textures.west_height = 0;
	vars->textures.east_width = 0;
	vars->textures.east_height = 0;
}

int get_texture_color(t_image *texture, int x, int y)
{
    int color;
    char *pixel;

    if (x < 0 || x >= texture->line_length / 4 || y < 0 || y >= texture->bits_per_pixel / 8)
        return 0; // Out of bounds check

    pixel = texture->addr + (y * texture->line_length + x * (texture->bits_per_pixel / 8));
    color = *(unsigned int *)pixel;

    return color;
}

void texture_load(t_vars *vars)
{
	vars->textures.north_image = mlx_xpm_file_to_image(vars->mlx, vars->textures.north, &vars->textures.north_width, &vars->textures.north_height);
	vars->textures.south_image = mlx_xpm_file_to_image(vars->mlx, vars->textures.south, &vars->textures.south_width, &vars->textures.south_height);
	vars->textures.west_image = mlx_xpm_file_to_image(vars->mlx, vars->textures.west, &vars->textures.west_width, &vars->textures.west_height);
	vars->textures.east_image = mlx_xpm_file_to_image(vars->mlx, vars->textures.east, &vars->textures.east_width, &vars->textures.east_height);
	if (!vars->textures.north_image || !vars->textures.south_image || !vars->textures.west_image || !vars->textures.east_image)
	{
		fprintf(stderr, "Error loading textures\n");
		exit(EXIT_FAILURE);
	}
}


static void	choose_texture(t_vars *vars, int x, int tex_x)
{
	t_image	*texture;
	int		y;

	if (vars->ray.side == 1)
	{
		if (vars->ray.step_y > 0)
			texture = vars->textures.south_image;
		else
			texture = vars->textures.north_image;
	}
	else
	{
		if (vars->ray.step_x > 0)
			texture = vars->textures.east_image;
		else
			texture = vars->textures.west_image;
	}
	y = 0;
	while (y == vars->ray.draw_start)
	{
		int texY = (((y * 256 - WIN_HEIGHT * 128 + vars->ray.line_height * 128) * vars->textures.north_height) / vars->ray.line_height) / 256;
		int color = get_texture_color(texture, tex_x, texY);
		my_mlx_pixel_put_int(&vars->image, x, y, color);
		y++;
	}
}

void	textre_calculation(t_vars *vars, int x)
{
	double	wall_x;
	int 	tex_x;

	if (vars->ray.side == 0)
		wall_x = vars->pos_y + vars->ray.perp_wall_dist * vars->ray.ray_dir_y;
	else
		wall_x = vars->pos_x + vars->ray.perp_wall_dist * vars->ray.ray_dir_x;
	wall_x -= floor(wall_x);

	tex_x = (int)(wall_x * (double)(vars->textures.north_width));
	if (vars->ray.side == 0 && vars->ray.ray_dir_x > 0)
		tex_x = vars->textures.north_width - tex_x - 1;
	if (vars->ray.side == 1 && vars->ray.ray_dir_y < 0)
		tex_x = vars->textures.north_width - tex_x - 1;
	choose_texture(vars, x, tex_x);
}