#include "libsbs.h"
#include <stdlib.h>

void	*sbs_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	total;

	total = count * size;
	if (count != 0 && total / count != size)
		return (NULL);
	ptr = malloc(total);
	if (ptr == NULL)
		return (NULL);
	sbs_memset(ptr, 0, total);
	return (ptr);
}
