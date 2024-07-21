#include "libft.h"

void	*ft_stackpop(t_stack *stack)
{
	void	*content;
	t_list	*temp;

	if (stack->count == 0)
		return (ft_putstr_fd("You can't pop when stack is empty!!",
				STDERR_FILENO), NULL);
	content = stack->top->content;
	temp = stack->top;
	stack->top = stack->top->next;
	ft_lstdelone(temp, NULL);
	stack->count--;
	return (content);
}
