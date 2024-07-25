#include "libft.h"
#include <math.h>
#include <stdio.h>

float	ft_vec_dot(t_vec vec1, t_vec vec2)
{
	float	res;

	res = 0;
	res += vec1.x * vec2.x;
	res += vec1.y * vec2.y;
	return (res);
}

float	ft_vec_distance(t_vec point1, t_vec point2)
{
	float	dist_x;
	float	dist_y;

	dist_x = fabs(point1.x - point2.x);
	dist_y = fabs(point1.y - point2.y);
	return (sqrtf(powf(dist_x, 2) + powf(dist_y, 2)));
}

float	ft_vec_mag(t_vec vec)
{
	t_vec	vec_null;

	vec_null.x = 0;
	vec_null.y = 0;
	return (ft_vec_distance(vec_null, vec));
}
