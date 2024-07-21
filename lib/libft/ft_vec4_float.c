#include "libft.h"

float	ft_vec4_dot(t_vec4 vec1, t_vec4 vec2)
{
	float	res;

	res = 0;
	res += vec1.x * vec2.x;
	res += vec1.y * vec2.y;
	res += vec1.z * vec2.z;
	res += vec1.w * vec2.w;
	return (res);
}

float	ft_vec4_mag(t_vec4 vec)
{
	return (sqrt(ft_vec4_dot(vec, vec)));
}
