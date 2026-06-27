#include "libsbs.h"
#include <stdlib.h>

char	*sbs_strdup(const char *s)
{
	size_t	len;
	size_t	i;
	char	*dup;

	len = sbs_strlen(s);
	dup = (char *)malloc(len + 1);
	if (dup == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dup[i] = s[i];
		i++;
	}
	dup[len] = '\0';
	return (dup);
}
