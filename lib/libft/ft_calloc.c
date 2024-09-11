#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*res;
	size_t	buffsize;

	buffsize = nmemb * size;
	res = malloc(buffsize);
	if (res == NULL)
		return (res);
	ft_bzero(res, buffsize);
	return (res);
}
