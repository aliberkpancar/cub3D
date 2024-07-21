#include "libft.h"
#include <stdio.h>

void	ft_put_pixel(t_image *image, int x, int y, t_color color)
{
	// if (x < 0 || x >= image->size_line || y < 0 || y >= image->line_count)
	// 	return;
	image->data[x + (image->size_line * y)] = color;
}

void	ft_fill_image(t_win *win, t_image *image, t_color color)
{
	int	i;
	int	j;

	i = 0;
	while (i < win->width)
	{
		j = 0;
		while (j < win->height)
		{
			ft_put_pixel(image, i, j, color);
			j++;
		}
		i++;
	}
}
