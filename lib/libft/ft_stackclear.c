#include "libft.h"

void	ft_stackclear(t_stack *stack, void (*del)(void *))
{
	ft_lstclear(&stack->top, del);
	free(stack);
}
