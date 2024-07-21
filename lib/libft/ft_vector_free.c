#include "libft.h"

void	ft_vector_free(void *vector)
{
	free(ft_vector_head(vector));
}
