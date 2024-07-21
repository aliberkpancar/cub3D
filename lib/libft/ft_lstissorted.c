#include "libft.h"

t_bool	ft_lstissorted(t_list *lst, t_bool (*comp)(void *con1, void *con2))
{
	if (lst == NULL)
		return (true);
	if (comp == NULL)
		return (false);
	while (lst->next != NULL)
	{
		if (comp(lst->content, lst->next->content))
			return (false);
		lst = lst->next;
	}
	return (true);
}
