#include "libft.h"

t_string	ft_string_new(char *str)
{
	t_string	new;

	if (str == NULL)
		return (NULL);
	new = ft_vector_new(sizeof (char));
	if (new == NULL)
		return (NULL);
	while (*str)
	{
		ft_vector_append(&new, str);
		str++;
	}
	ft_vector_append(&new, str);
	return (new);
}
