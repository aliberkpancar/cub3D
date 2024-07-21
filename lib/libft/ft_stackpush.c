#include "libft.h"

void	ft_stackpush(t_stack *stack, void *content)
{
	t_list	*lst_content;

	lst_content = ft_lstnew(content);
	if (lst_content == NULL)
		return ;
	ft_lstadd_front(&stack->top, lst_content);
	stack->count++;
}
