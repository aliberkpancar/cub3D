#include "cub3d.h"

void	rotate_index(t_image *tex)
{
	int	i;
	int	j;

	i = 0;
	while (i < tex->size_line)
	{
		j = i;
		while (j < tex->line_count)
		{
			ft_swap_int((int *)(&(tex->data[j + (tex->size_line * i)].value)),
				(int *)(&(tex->data[i + (tex->line_count * j)].value)));
			j++;
		}
		i++;
	}
}

void	mirror_tex(t_image *tex)
{
	int	i;
	int	j;

	j = 0;
	while (j < tex->size_line)
	{
		i = 0;
		while (i < tex->line_count / 2)
		{
			ft_swap_int((int *)(&tex->data[j + (i * tex->size_line)].value),
				(int *)(&tex->data[j + ((tex->size_line - i - 1)
						* tex->size_line)].value));
			i++;
		}
		j++;
	}
}

float	get_tex_y(t_image *tex, float i, float height)
{
	if (i < 0 || height <= 0)
	{
		printf("Error\nInvalid values for i or height\n");
		return (0.0f);
	}
	return (linear_interpolation(ft_normalize(i, 0, height), 0,
			tex->size_line));
}

void	draw_tex_helper(int *i, float *tex_y,
	float *full_height, float *line_height)
{
	*i = 0;
	*tex_y = 0;
	if (*line_height < 0)
	{
		printf("Error\nLine_height is negative: %f\n", *line_height);
		*line_height = 0;
	}
	*full_height = *line_height;
	if (*line_height > HEIGHT)
		*line_height = HEIGHT;
}

t_color	*get_tex_data(t_image *tex, float tex_x)
{
	return (tex->data + ((int)linear_interpolation(tex_x, 0, tex->size_line)
			* tex->size_line));
}
