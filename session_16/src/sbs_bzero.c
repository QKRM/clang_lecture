#include "libsbs.h"

void	sbs_bzero(void *s, size_t n)
{
	sbs_memset(s, 0, n);
}
