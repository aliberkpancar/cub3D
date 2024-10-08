/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apancar <apancar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:15:45 by apancar           #+#    #+#             */
/*   Updated: 2024/10/03 12:15:46 by apancar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	float	height;
	t_color	*data;

	height = HEIGHT;
	data = fetch_texture_data(drw.tex, drw.tex_x);
	if (!data)
		return ;
	i = 0;
	setup_texture_rendering(&i, &tex_y, &height, &drw.line_height);
	while (i < drw.line_height)
	{
		if (height > HEIGHT)
			tex_y = calculate_texture_y(drw.tex, height, i + \
			((height - HEIGHT) / 2));
		else
			tex_y = calculate_texture_y(drw.tex, drw.line_height, i);
		if (tex_y >= drw.tex->size_line)
			tex_y = drw.tex->size_line - 1;
		ft_put_pixel(&drw.vars->mlx.image, drw.index,
			i + (HEIGHT - drw.line_height) / 2, data[(int)tex_y]);
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

static t_bool	ft_vec_equal(t_vec vec1, t_vec vec2)
{
	if (((fabs(vec1.x) - fabs(vec2.x)) < 0.001)
		&& (fabs(vec1.y) - fabs(vec2.y) < 0.001))
		return (true);
	return (false);
}

void	draw_walls(t_vars *vars)
{
	float	line_height;
	float	ray_len;
	int		i;
	t_vec	null;

	i = 0;
	null = (t_vec){.x = 0, .y = 0};
	while (i < vars->num_of_rays)
	{
		if (ft_vec_equal(vars->collisions[i].pos, null))
		{
			i++;
			continue ;
		}
		ray_len = ft_vec_distance(vars->collisions[i].pos, vars->player.pos);
		if (ray_len == 0)
			continue ;
		line_height = HEIGHT / (ray_len
				* cos(degree_to_radian(vars->ray_angle[i])));
		draw_wall_piece(vars, line_height, i, vars->collisions[i].face);
		i++;
	}
}
