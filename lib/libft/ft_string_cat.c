#include "libft.h"

size_t	ft_string_cat(t_string *dst, char *src)
{
	if (dst == NULL || src == NULL)
		return (0);
	ft_vector_pop(dst, NULL);
	while (*src)
	{
		ft_vector_append(dst, src);
		src++;
	}
	ft_vector_append(dst, src);
	return (ft_vector_len(dst));
}
