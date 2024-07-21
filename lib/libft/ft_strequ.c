#include "libft.h"

t_bool	ft_strequ(const char *s1, const char *s2)
{
	if (!s1 || !s2)
		return (error);
	if (ft_strlen(s1) != ft_strlen(s2))
		return (false);
	while (*s1)
	{
		if (*s1 - *s2)
			return (false);
		s2++;
		s1++;
	}
	return (true);
}
