#include "libft.h"

t_bool	ft_strcheck(char *str, t_bool (*cond)(int))
{
	int	i;

	i = 0;
	while (str[i])
		if (!cond(str[i++]))
			return (0);
	return (1);
}
