#include "cub3d.h"

void	draw_background(t_vars *vars)
{
	int	i;
	int	j;

	i = 0;
	while (i < WIDTH)
	{
		j = 0;
		while (j < HEIGHT)
		{
			if (j <= HEIGHT / 2)
				ft_put_pixel(&vars->mlx.image, i, j, vars->ceiling);
			else
				ft_put_pixel(&vars->mlx.image, i, j, vars->floor);
			j++;
		}
		i++;
	}
}

static void	draw_face(struct s_draw_hlpr drw)
{
	int		i;
	float	tex_y;
	float	full_height;
	t_color	*data;

	// drw.line_height = HEIGHT;
	full_height = HEIGHT;
	data = get_tex_data(drw.tex, drw.tex_x);
	if (!data)
	{
		printf("Error : Texture data is null.\n");
		return ;
	}
	i = 0;
	draw_tex_helper(&i, &tex_y, &full_height, &drw.line_height);
	while (i < drw.line_height)
	{
		if (full_height > HEIGHT)
		{
			tex_y = get_tex_y(drw.tex, i + ((full_height - HEIGHT) / 2),
					full_height);
		}
		else
			tex_y = get_tex_y(drw.tex, i,
					drw.line_height);
		if (tex_y >= drw.tex->size_line)
			tex_y = drw.tex->size_line - 1;
		ft_put_pixel(&drw.vars->mlx.image, drw.index,
			i + (HEIGHT - drw.line_height) / 2,
			data[(int)tex_y]);
		i++;
	}
}

static void	draw_wall_piece(t_vars *vars, float line_height,
	int index, t_face face)
{
	float	pos_x;
	float	pos_y;

	pos_x = vars->collisions[index].pos.x;
	pos_y = vars->collisions[index].pos.y;
	if (face == south)
		draw_face((struct s_draw_hlpr){.vars = vars, .tex = &vars->tex_south,
			.line_height = line_height, .index = index,
			.tex_x = pos_x - (int)pos_x});
	if (face == west)
		draw_face((struct s_draw_hlpr){.vars = vars, .tex = &vars->tex_west,
			.line_height = line_height, .index = index,
			.tex_x = pos_y - (int)pos_y});
	if (face == north)
		draw_face((struct s_draw_hlpr){.vars = vars, .tex = &vars->tex_north,
			.line_height = line_height, .index = index,
			.tex_x = pos_x - (int)pos_x});
	if (face == east)
		draw_face((struct s_draw_hlpr){.vars = vars, .tex = &vars->tex_east,
			.line_height = line_height, .index = index,
			.tex_x = pos_y - (int)pos_y});
}
static t_bool	ft_vec2_equ(t_vec2 vec1, t_vec2 vec2)
{
	if (((fabs(vec1.x) - fabs(vec2.x)) < EPSILON) && (fabs(vec1.y) - fabs(vec2.y) < EPSILON))
		return (true);
	return (false);
}

void	draw_walls(t_vars *vars)
{
	float	line_height;
	float	ray_len;
	int		i;

	i = 0;
	while (i < vars->coll_count)
	{
		if (ft_vec2_equ(vars->collisions[i].pos, g_vec2_null))
		{
			i++;
			continue ;
		}
		ray_len = ft_vec2_dist(vars->collisions[i].pos, vars->player.pos);
		line_height = HEIGHT
			/ (ray_len * cos(degree_to_radian(vars->coll_degree[i])));
		draw_wall_piece(vars, line_height, i, vars->collisions[i].face);
		i++;
	}
}
