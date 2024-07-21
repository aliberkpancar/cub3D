#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*link;

	link = malloc(sizeof(t_list));
	if (link == NULL)
		return (NULL);
	link->content = content;
	link->next = NULL;
	return (link);
}
