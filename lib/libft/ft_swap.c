#include "libft.h"
#include <stdio.h>

void	ft_swap_int(int *a, int *b)
{
	if (!a || !b)
	{
		printf("Error: ft_swap_int: NULL pointer\n");	
		return ;
	}
	if (a == b)
		return ;
		
	*a = *a ^ *b;
	*b = *a ^ *b;
	*a = *a ^ *b;
}
