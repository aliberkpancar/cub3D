#include "libft.h"

void	ft_lstswap(t_list *first, t_list *second)
{
	void	*temp;

	if (first == NULL || second == NULL)
		return ;
	temp = first->content;
	first->content = second->content;
	second->content = temp;
}
