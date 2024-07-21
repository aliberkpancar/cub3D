#include "libft.h"

float	ft_normalize(float val, float min, float max)
{
	if (max == min)
		return (1);
	return ((val - min) / (max - min));
}

float	ft_lerp(float val, float min, float max)
{
	return ((val * (max - min)) + min);
}

float	ft_map(float val, t_map map)
{
	return (ft_lerp(ft_normalize(val, map.min_i, map.min_o),
			map.min_o, map.max_o));
}

t_map	ft_map_init(float min_i, float max_i, float min_o, float max_o)
{
	t_map	map;

	map.max_i = max_i;
	map.max_o = max_o;
	map.min_i = min_i;
	map.min_o = min_o;
	return (map);
}
