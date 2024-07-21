#include "libft.h"

void	*ft_new(void *data, t_types type)
{
	void	*entry;

	entry = malloc(type);
	if (entry == NULL)
		return (NULL);
	ft_memcpy(entry, data, type);
	return (entry);
}
