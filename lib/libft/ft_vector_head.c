#include "libft.h"

t_vector	*ft_vector_head(void *vector)
{
	return ((t_vector *)(vector - (sizeof (size_t) * 3)));
}
