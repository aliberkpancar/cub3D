#include "libft.h"

float	degree_to_radian(float degree)
{
	return ((degree / 180) * PI);
}

float	ft_rad_to_deg(float rad)
{
	return (rad * (180 / PI));
}
