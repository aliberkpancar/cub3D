#include "libft.h"

size_t	ft_vector_len(void *vector)
{
	return (ft_vector_head(*((char **)vector))->lenght);
}
