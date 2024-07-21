#include "libft.h"

void	ft_vector_clear(void *vector_adrr)
{
	t_vector	*vector;
	int			i;

	if (vector_adrr == NULL)
		return ;
	vector = *(char **)vector_adrr;
	i = ft_vector_len(vector);
	while (i > 0)
	{
		ft_vector_pop(vector_adrr, NULL);
		i--;
	}
}
