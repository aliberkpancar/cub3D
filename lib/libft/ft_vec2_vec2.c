#include "libft.h"

t_vec2	ft_vec2_inv(t_vec2 vector)
{
	t_vec2	vec2_res;

	vec2_res.x = -vector.x;
	vec2_res.y = -vector.y;
	return (vec2_res);
}

t_vec2	ft_vec2_norm(t_vec2 vector)
{
	return (ft_vec2_div(vector, ft_vec2_mag(vector)));
}

t_vec2	ft_vec2_rotate(t_vec2 vector, float degree)
{
	t_vec2	rotated_vector;
	float	radian;

	radian = ft_deg_to_rad(degree);
	rotated_vector.x = ((vector.x * cos(radian)) - (vector.y * sin(radian)));
	rotated_vector.y = ((vector.x * sin(radian)) + (vector.y * cos(radian)));
	return (rotated_vector);
}
