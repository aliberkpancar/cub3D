#include "libft.h"

t_vec4	ft_vec4_norm(t_vec4 vec)
{
	return (ft_vec4_div(vec, ft_vec4_mag(vec)));
}
