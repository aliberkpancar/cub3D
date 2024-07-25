#include "libft.h"

t_vec	ft_vec_set(float x, float y)
{
	t_vec	vec_res;

	vec_res.x = x;
	vec_res.y = y;
	return (vec_res);
}

t_vec	ft_vec_add(t_vec vec1, t_vec vec2)
{
	t_vec	vec_res;

	vec_res.x = vec1.x + vec2.x;
	vec_res.y = vec1.y + vec2.y;
	return (vec_res);
}

t_vec	ft_vec_sub(t_vec	vec1, t_vec vec2)
{
	t_vec	vec_res;

	vec_res.x = vec1.x - vec2.x;
	vec_res.y = vec1.y - vec2.y;
	return (vec_res);
}

t_vec	ft_vec_mul(t_vec vec, float mul)
{
	t_vec	vec_res;

	vec_res.x = vec.x * mul;
	vec_res.y = vec.y * mul;
	return (vec_res);
}

t_vec	ft_vec_div(t_vec vec, float div)
{
	t_vec	vec_res;

	if (div == 0)
		return ((t_vec){.x = 0, .y = 0});
	vec_res.x = vec.x / div;
	vec_res.y = vec.y / div;
	return (vec_res);
}
