#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*newtemp;

	if (!lst || !del)
		return (NULL);
	new = ft_lstnew(f(lst->content));
	if (!new)
		return (NULL);
	newtemp = new;
	lst = lst->next;
	while (lst)
	{
		newtemp->next = ft_lstnew(f(lst->content));
		if (!(newtemp->next))
		{
			ft_lstclear(&new, del);
			return (NULL);
		}
		newtemp = newtemp->next;
		lst = lst->next;
	}
	newtemp->next = NULL;
	return (new);
}
