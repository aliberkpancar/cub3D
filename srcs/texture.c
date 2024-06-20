#include "../mlx/mlx.h"
#include "../includes/cub3d.h"

void texture_init(t_vars *vars)
{
	vars->texture.north = NULL;
	vars->texture.south = NULL;
	vars->texture.west = NULL;
	vars->texture.east = NULL;
	vars->texture.north_image = NULL;
	vars->texture.south_image = NULL;
	vars->texture.west_image = NULL;
	vars->texture.east_image = NULL;
	vars->texture.north_width = 0;
	vars->texture.north_height = 0;
	vars->texture.south_width = 0;
	vars->texture.south_height = 0;
	vars->texture.west_width = 0;
	vars->texture.west_height = 0;
	vars->texture.east_width = 0;
	vars->texture.east_height = 0;
}

static int get_texture_color(t_image *text, int x, int y)
{
    int		color;
    char	*pixel;

	color = 0;
    if (x < 0 || x >= text->width || y < 0 || y >= text->height)
        return (1);
    pixel = text->addr + (y * text->line_length + x * (text->bits_per_pixel / 8));
    color = *(unsigned int *)pixel;
    return (color);
}

static void texture_load(t_vars *vars)
{
	vars->texture.north_image = mlx_xpm_file_to_image(vars->mlx, vars->texture.north, &vars->texture.north_width, &vars->texture.north_height);
	vars->texture.south_image = mlx_xpm_file_to_image(vars->mlx, vars->texture.south, &vars->texture.south_width, &vars->texture.south_height);
	vars->texture.west_image = mlx_xpm_file_to_image(vars->mlx, vars->texture.west, &vars->texture.west_width, &vars->texture.west_height);
	vars->texture.east_image = mlx_xpm_file_to_image(vars->mlx, vars->texture.east, &vars->texture.east_width, &vars->texture.east_height);
	if (!vars->texture.north_image || !vars->texture.south_image || !vars->texture.west_image || !vars->texture.east_image)
	{
		fprintf(stderr, "Error loading texture\n");
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
			texture = vars->texture.south_image;
		else
			texture = vars->texture.north_image;
	}
	else
	{
		if (vars->ray.step_x > 0)
			texture = vars->texture.east_image;
		else
			texture = vars->texture.west_image;
	}
	y = vars->ray.draw_start;
	while (y <= vars->ray.draw_end)
	{
		int texY = (((y * 256 - WIN_HEIGHT * 128 + vars->ray.line_height * 128) * vars->texture.north_height) / vars->ray.line_height) / 256;
		int color = get_texture_color(texture, tex_x, texY);
		my_mlx_pixel_put_int(&vars->image, x, y, color);
		y++;
	}
}

void	texture_calculation(t_vars *vars, int x)
{
	double	wall_x;
	int 	tex_x;

	if (vars->ray.side == 0)
		wall_x = vars->pos_y + vars->ray.perp_wall_dist * vars->ray.ray_dir_y;
	else
		wall_x = vars->pos_x + vars->ray.perp_wall_dist * vars->ray.ray_dir_x;
	wall_x -= floor(wall_x);

	tex_x = (int)(wall_x * (double)(vars->texture.north_width));
	if (vars->ray.side == 0 && vars->ray.ray_dir_x > 0)
		tex_x = vars->texture.north_width - tex_x - 1;
	if (vars->ray.side == 1 && vars->ray.ray_dir_y < 0)
		tex_x = vars->texture.north_width - tex_x - 1;
	choose_texture(vars, x, tex_x);
}

void handle_texture(t_vars *vars)
{
	vars->texture.north = "../texture/path_to_north_texture.xpm";
    vars->texture.south = "../texture/path_to_south_texture.xpm";
    vars->texture.west = "../texture/path_to_west_texture.xpm";
    vars->texture.east = "../texture/path_to_east_texture.xpm";
	texture_load(vars);
	texture_calculation(vars, 0);
}
