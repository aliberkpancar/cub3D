#include "libft.h"
#include <math.h>
#include <stdio.h>

float	ft_vec2_dot(t_vec2 vec1, t_vec2 vec2)
{
	float	res;

	res = 0;
	res += vec1.x * vec2.x;
	res += vec1.y * vec2.y;
	return (res);
}

float	ft_vec2_dist(t_vec2 point1, t_vec2 point2)
{
	float	dist_x;
	float	dist_y;

	dist_x = fabs(point1.x - point2.x);
	dist_y = fabs(point1.y - point2.y);
	return (sqrtf(powf(dist_x, 2) + powf(dist_y, 2)));
}

float	ft_vec2_mag(t_vec2 vec)
{
	t_vec2	vec_null;

	vec_null.x = 0;
	vec_null.y = 0;
	return (ft_vec2_dist(vec_null, vec));
}
