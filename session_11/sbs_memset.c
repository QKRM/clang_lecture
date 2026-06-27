#include "libsbs.h"

/* 10차시에서 구현한 sbs_memset (calloc이 내부에서 사용) */
void	*sbs_memset(void *b, int c, size_t len)
{
	unsigned char	*p;
	size_t			i;

	p = (unsigned char *)b;
	i = 0;
	while (i < len)
	{
		p[i] = (unsigned char)c;
		i++;
	}
	return (b);
}
