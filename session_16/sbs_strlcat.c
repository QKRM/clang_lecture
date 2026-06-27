#include "libsbs.h"

size_t	sbs_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dstlen;
	size_t	srclen;
	size_t	i;

	srclen = sbs_strlen(src);
	if (dstsize == 0)
		return (srclen);
	dstlen = 0;
	while (dstlen < dstsize && dst[dstlen])
		dstlen++;
	if (dstlen == dstsize)
		return (dstsize + srclen);
	i = 0;
	while (src[i] && dstlen + i < dstsize - 1)
	{
		dst[dstlen + i] = src[i];
		i++;
	}
	dst[dstlen + i] = '\0';
	return (dstlen + srclen);
}
