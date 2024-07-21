#include "libft.h"

size_t	ft_vector_insert(void *vector_adrr, void *val, const size_t index)
{
	t_vector	*head;

	head = ft_vector_head(*(char **)vector_adrr);
	if (head->lenght == head->buffer_size / head->type_size)
	{
		head = ft_vector_grow(vector_adrr, head, head->buffer_size);
		if (head == NULL)
			return (-1);
	}
	ft_memmove(&head->buffer[(index + 1) * head->type_size],
		&head->buffer[index * head->type_size],
		(head->lenght - index) * head->type_size);
	ft_memcpy(&head->buffer[index * head->type_size], val, head->type_size);
	head->lenght++;
	return (head->lenght);
}
