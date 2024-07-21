#include "libft.h"
#include <stdio.h>

int	ft_pow(int base, unsigned int power)
{
	while (power > 1)
	{
		base *= base;
		power--;
	}
	return base;
}

size_t	ft_hash(void *data, size_t size)
{
	unsigned int	i;
	unsigned int	res;

	i = 0;
	res = 0;
	while (i < size)
	{
		res += (*(char *)(data + i) * ft_pow(31, size - i));
		i++;
	}
	return (res);
}
