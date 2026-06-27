#include <string.h>
#include <stdio.h>
#include "libsbs.h"

/*
 * strlcat 정답 동작 (oracle):
 *  - dst의 기존 문자열 뒤에 src를 이어붙임 (버퍼 안전)
 *  - 반환값 = 초기 dstlen + srclen (단, dstlen은 min(dstsize, 실제 길이))
 *  - dst가 dstsize 안에 \0이 없으면 반환 = dstsize + srclen
 * glibc에 strlcat이 없을 수 있어 oracle을 직접 구현해 비교.
 */
static size_t	oracle_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dstlen;
	size_t	srclen;
	size_t	i;

	srclen = strlen(src);
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

int	main(int argc, char **argv)
{
	int		pass;
	int		total;
	int		verbose;
	char	*inits[] = {"", "abc", "Hello"};
	char	*srcs[] = {"", "XY", "world!"};
	size_t	sizes[] = {0, 1, 4, 8, 32};
	int		ii;
	int		si;
	size_t	zi;

	verbose = (argc > 1 && strcmp(argv[1], "-v") == 0);
	pass = 0;
	total = 0;
	ii = 0;
	while (ii < 3)
	{
		si = 0;
		while (si < 3)
		{
			zi = 0;
			while (zi < 5)
			{
				char	a[64];
				char	b[64];
				memset(a, 0, 64);
				memset(b, 0, 64);
				strcpy(a, inits[ii]);
				strcpy(b, inits[ii]);
				size_t ra = oracle_strlcat(a, srcs[si], sizes[zi]);
				size_t rb = sbs_strlcat(b, srcs[si], sizes[zi]);
				total++;
				if (ra == rb && memcmp(a, b, 64) == 0)
					pass++;
				else if (verbose)
					printf("  init=\"%s\" src=\"%s\" size=%zu 불일치 (%zu/%zu)\n",
						inits[ii], srcs[si], sizes[zi], ra, rb);
				zi++;
			}
			si++;
		}
		ii++;
	}
	printf("%d/%d\n", pass, total);
	return (pass != total);
}
