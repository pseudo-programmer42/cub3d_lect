#include <stdlib.h>

char	*ft_strdup(const char *s1)
{
	size_t	len;
	char	*res;
	char	*c;

	len = 0;
	while (*s1++)
		len++;
	len++;
	s1 -= len;
	if (!(res = (char*)malloc(sizeof(char) * len)))
		return (0);
	c = res;
	while (*s1)
		*c++ = *s1++;
	*c = 0;
	return (res);
}
