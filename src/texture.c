/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apancar <apancar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:16:42 by apancar           #+#    #+#             */
/*   Updated: 2024/10/03 12:16:43 by apancar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	flip_texture(t_image *texture)
{
	int	row;
	int	half_col;

	half_col = 0;
	while (half_col < texture->size_line)
	{
		row = 0;
		while (row < texture->line_count / 2)
		{
			swap_integers((int *) \
			(&texture->data[half_col + (row * texture->size_line)].value), \
			(int *)(&texture->data[half_col + ((texture->size_line - row - 1) \
			* texture->size_line)].value));
			row++;
		}
		half_col++;
	}
}

float	calculate_texture_y(t_image *texture, float height, float position)
{
	if (position < 0 || height <= 0)
	{
		printf("Error\nInvalid values for position or height\n");
		return (0.0f);
	}
	return (linear_interpolation(ft_normalize(position, 0, height), 0,
			texture->size_line));
}

void	setup_texture_rendering(int *i, float *texture_y,
	float *full_height, float *line_height)
{
	*i = 0;
	*texture_y = 0;
	if (*line_height < 0)
	{
		printf("Error\nLine_height is negative: %f\n", *line_height);
		*line_height = 0;
	}
	*full_height = *line_height;
	if (*line_height > HEIGHT)
		*line_height = HEIGHT;
}

t_color	*fetch_texture_data(t_image *texture, float texture_x)
{
	return (texture->data + \
	((int)linear_interpolation(texture_x, 0, texture->size_line) \
	* texture->size_line));
}

void	transform_texture(t_image *texture)
{
	int	row;
	int	col;

	row = 0;
	while (row < texture->size_line)
	{
		col = row;
		while (col < texture->line_count)
		{
			swap_integers((int *)(&(texture->data[col + \
			(texture->size_line * row)].value)), \
			(int *)(&(texture->data[row + (texture->line_count * col)].value)));
			col++;
		}
		row++;
	}
}
