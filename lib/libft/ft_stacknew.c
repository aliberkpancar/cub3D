#include "libft.h"

t_stack	*ft_stacknew(void)
{
	t_stack	*stack;

	stack = malloc(sizeof(t_stack));
	if (stack == NULL)
		return (NULL);
	stack->count = 0;
	return (stack);
}
