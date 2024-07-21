#include "libft.h"

void	*ft_malloc(size_t nmemb, size_t size)
{
	void	*allocated;

	allocated = malloc(nmemb * size);
	if (allocated == NULL)
		return (NULL);
	return (allocated);
}
