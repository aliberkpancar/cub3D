#include "libft.h"
#include <stdio.h>

void	ft_put_pixel(t_image *image, int x, int y, t_color color)
{
	image->data[x + (image->size_line * y)] = color;
}
