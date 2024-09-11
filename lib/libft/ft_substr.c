#include "libft.h"

char	*ft_substr(char const *s, int start, int len)
{
	char		*substr;

	if (s == NULL)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	substr = malloc(len + 1);
	if (substr == NULL)
		return (NULL);
	ft_strlcpy(substr, (char *)s + start, len + 1);
	return (substr);
}
