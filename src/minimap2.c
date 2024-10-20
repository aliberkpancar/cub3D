/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apancar <apancar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:16:20 by apancar           #+#    #+#             */
/*   Updated: 2024/10/17 09:27:54 by apancar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_draw_circle(t_mlx *mlx, int *center, int radius, int color)
{
	int	x;
	int	y;
	int	sq_radius;

	sq_radius = radius * radius;
	y = -radius;
	while (y <= radius)
	{
		x = -radius;
		while (x <= radius)
		{
			if (x * x + y * y <= sq_radius)
				mlx_pixel_put(mlx->mlx, mlx->win.win,
					center[0] + x, center[1] + y, color);
			x++;
		}
		y++;
	}
}

void	ft_draw_rect(t_mlx *mlx, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < 10)
	{
		j = 0;
		while (j < 10)
		{
			mlx_pixel_put(mlx->mlx, mlx->win.win, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

void	ft_sketch_line(t_mlx *mlx, t_vec pt1, t_vec pt2, t_color color)
{
	struct s_mini_temp	tmp;
	int					i;

	if (fabs(pt2.x - pt1.x) > fabs(pt2.y - pt1.y))
		tmp.steps = fabs(pt2.x - pt1.x);
	else
		tmp.steps = fabs(pt2.y - pt1.y);
	tmp.x_inc = (pt2.x - pt1.x) / (float)tmp.steps;
	tmp.y_inc = (pt2.y - pt1.y) / (float)tmp.steps;
	tmp.x = pt1.x;
	tmp.y = pt1.y;
	i = 0;
	while (i <= tmp.steps)
	{
		mlx_pixel_put(mlx->mlx, mlx->win.win,
			(int)tmp.x, (int)tmp.y, color.value);
		tmp.x += tmp.x_inc;
		tmp.y += tmp.y_inc;
		i++;
	}
}

t_vec	set_vals(float x, float y)
{
	t_vec	tmp;

	tmp.x = x;
	tmp.y = y;
	return (tmp);
}
