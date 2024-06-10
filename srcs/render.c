#include "../includes/cub3d.h"
#include "../mlx/mlx.h"
#include <math.h>
#include <stdio.h>

#define WIN_WIDTH 800
#define WIN_HEIGHT 600

// static void	my_mlx_pixel_put(t_image *image, int x, int y, t_color color)
// {
// 	char	*dst;
// 	unsigned int	pixel_color;

// 	dst = image->addr + (y * image->line_length + x * (image->bits_per_pixel / 8));
// 	pixel_color = (color.r << 16) | (color.g << 8) | color.b;
// 	*(unsigned int *)dst = pixel_color;
// }


void	my_mlx_pixel_put_int(t_image *image, int x, int y, int color)
{
	char	*dst;

	dst = image->addr + (y * image->line_length + x * (image->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

static void draw_vertical_line(t_vars *vars, int x, int draw_start, int draw_end, int color)
{
    for (int y = draw_start; y < draw_end; y++)
    {
        my_mlx_pixel_put_int(&vars->image, x, y, color);
    }
}


void render_scene(t_vars *vars)
{
    for (int x = 0; x < WIN_WIDTH; x++)
    {
        double camera_x = 2 * x / (double)WIN_WIDTH - 1; // X-coordinate in camera space
        vars->ray.ray_dir_x = vars->dir_x + vars->plane_x * camera_x;
        vars->ray.ray_dir_y = vars->dir_y + vars->plane_y * camera_x;
        vars->ray.map_x = (int)vars->pos_x;
        vars->ray.map_y = (int)vars->pos_y;

        // Length of ray from current position to next x or y-side
        vars->ray.delta_dist_x = fabs(1 / vars->ray.ray_dir_x);
        vars->ray.delta_dist_y = fabs(1 / vars->ray.ray_dir_y);

        vars->ray.hit = 0;

        // Calculate step and initial sideDist
        if (vars->ray.ray_dir_x < 0)
        {
            vars->ray.step_x = -1;
            vars->ray.side_dist_x = (vars->pos_x - vars->ray.map_x) * vars->ray.delta_dist_x;
        }
        else
        {
            vars->ray.step_x = 1;
            vars->ray.side_dist_x = (vars->ray.map_x + 1.0 - vars->pos_x) * vars->ray.delta_dist_x;
        }
        if (vars->ray.ray_dir_y < 0)
        {
            vars->ray.step_y = -1;
            vars->ray.side_dist_y = (vars->pos_y - vars->ray.map_y) * vars->ray.delta_dist_y;
        }
        else
        {
            vars->ray.step_y = 1;
            vars->ray.side_dist_y = (vars->ray.map_y + 1.0 - vars->pos_y) * vars->ray.delta_dist_y;
        }

        // Perform DDA
        while (vars->ray.hit == 0)
        {
            if (vars->ray.side_dist_x < vars->ray.side_dist_y)
            {
                vars->ray.side_dist_x += vars->ray.delta_dist_x;
                vars->ray.map_x += vars->ray.step_x;
                vars->ray.side = 0;
            }
            else
            {
                vars->ray.side_dist_y += vars->ray.delta_dist_y;
                vars->ray.map_y += vars->ray.step_y;
                vars->ray.side = 1;
            }

            // Boundary check before accessing the map
            if (vars->ray.map_x < 0 || vars->ray.map_x >= vars->map_width || vars->ray.map_y < 0 || vars->ray.map_y >= vars->map_height)
            {
                vars->ray.hit = 1; // Set hit to 1 to break out of the loop
                break;
            }
            if (vars->map[vars->ray.map_y][vars->ray.map_x] == '1')
                vars->ray.hit = 1;
        }

        // Calculate distance to the point of impact
        if (vars->ray.side == 0)
            vars->ray.perp_wall_dist = (vars->ray.map_x - vars->pos_x + (1 - vars->ray.step_x) / 2) / vars->ray.ray_dir_x;
        else
            vars->ray.perp_wall_dist = (vars->ray.map_y - vars->pos_y + (1 - vars->ray.step_y) / 2) / vars->ray.ray_dir_y;

        vars->ray.line_height = (int)(WIN_HEIGHT / vars->ray.perp_wall_dist);

        vars->ray.draw_start = -vars->ray.line_height / 2 + WIN_HEIGHT / 2;
        if (vars->ray.draw_start < 0)
            vars->ray.draw_start = 0;
        vars->ray.draw_end = vars->ray.line_height / 2 + WIN_HEIGHT / 2;
        if (vars->ray.draw_end >= WIN_HEIGHT)
            vars->ray.draw_end = WIN_HEIGHT - 1;

        int color;
        if (vars->ray.side == 1)
        {
            color = 0xFF0000;
        }
        else
        {
            color = 0x00FF00;
        }
		textre_calculation(vars, x);
        draw_vertical_line(vars, x, vars->ray.draw_start, vars->ray.draw_end, color);
    }
    mlx_put_image_to_window(vars->mlx, vars->win, vars->image.image, 0, 0);
}


int	main_loop(t_vars *vars)
{
	render_scene(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->image.image, 0, 0);
	return (0);
}