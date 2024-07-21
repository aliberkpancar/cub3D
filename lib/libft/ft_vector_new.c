#include "libft.h"

void	*ft_vector_new(size_t type_size_b)
{
	t_vector	*vector;

	vector = ft_calloc(1, (sizeof(t_vector) - 8 + (type_size_b * 1)));
	if (vector == NULL)
		return (NULL);
	vector->type_size = type_size_b;
	vector->lenght = 0;
	vector->buffer_size = type_size_b * 1;
	return (&vector->buffer);
}
