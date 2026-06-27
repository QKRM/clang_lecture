#include <string.h>
#include <stdio.h>
#include "libsbs.h"

/*
 * strlcpy 정답 동작 (oracle):
 *  - 반환값 = src 길이
 *  - dstsize>0이면 최대 dstsize-1 글자 복사 + '\0'
 *  - dstsize==0이면 아무것도 안 씀
 * glibc에 strlcpy가 없을 수 있어 oracle을 직접 구현해 비교.
 */
static size_t	oracle_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	srclen;
	size_t	i;

	srclen = strlen(src);
	if (dstsize == 0)
		return (srclen);
	i = 0;
	while (src[i] && i < dstsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (srclen);
}

int	main(int argc, char **argv)
{
	int		pass;
	int		total;
	int		verbose;
	char	*srcs[] = {"", "hi", "hello world"};
	size_t	sizes[] = {0, 1, 3, 6, 32};
	int		si;
	size_t	zi;

	verbose = (argc > 1 && strcmp(argv[1], "-v") == 0);
	pass = 0;
	total = 0;
	si = 0;
	while (si < 3)
	{
		zi = 0;
		while (zi < 5)
		{
			char	a[64];
			char	b[64];
			memset(a, 'X', 64);
			memset(b, 'X', 64);
			size_t ra = oracle_strlcpy(a, srcs[si], sizes[zi]);
			size_t rb = sbs_strlcpy(b, srcs[si], sizes[zi]);
			total++;
			if (ra == rb && memcmp(a, b, 64) == 0)
				pass++;
			else if (verbose)
				printf("  src=\"%s\" size=%zu 불일치 (ret %zu/%zu)\n",
					srcs[si], sizes[zi], ra, rb);
			zi++;
		}
		si++;
	}
	printf("%d/%d\n", pass, total);
	return (pass != total);
}
