#include "libft.h"

t_color	ft_set_color(__uint8_t a, __uint8_t r, __uint8_t g, __uint8_t b)
{
	t_color	color;

	color.alpha = a;
	color.red = r;
	color.green = g;
	color.blue = b;
	return (color);
}

t_color	ft_get_gradient_val(t_color from, t_color to, float value)
{
	t_color	color;

	color.red = ft_lerp(value, from.red, to.red);
	color.green = ft_lerp(value, from.green, to.green);
	color.blue = ft_lerp(value, from.blue, to.blue);
	return (color);
}

t_gradient	ft_set_gradient(t_color from, t_color to)
{
	t_gradient	grad;

	grad.from = from;
	grad.to = to;
	return (grad);
}

t_gradient	ft_inv_gradient(t_gradient in)
{
	t_gradient	out;

	out.from = in.to;
	out.to = in.from;
	return (out);
}
