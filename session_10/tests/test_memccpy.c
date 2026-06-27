#include <string.h>
#include <stdio.h>
#include "libsbs.h"

/* 표준 memccpy를 정답으로. 반환 포인터(찾으면 위치+1, 못 찾으면 NULL) + 버퍼 비교. */
int	main(int argc, char **argv)
{
	char	src[16] = "hello world";
	char	a[32];
	char	b[32];
	int		pass;
	int		total;
	int		verbose;
	int		stops[] = {'o', 'z', 'h', 'd'};
	size_t	lens[] = {0, 3, 8, 12};
	int		si;
	size_t	li;

	verbose = (argc > 1 && strcmp(argv[1], "-v") == 0);
	pass = 0;
	total = 0;
	si = 0;
	while (si < 4)
	{
		li = 0;
		while (li < 4)
		{
			memset(a, 0, 32);
			memset(b, 0, 32);
			void *ra = memccpy(a, src, stops[si], lens[li]);
			void *rb = sbs_memccpy(b, src, stops[si], lens[li]);
			total++;
			if (memcmp(a, b, 32) == 0
				&& ((ra == NULL && rb == NULL)
					|| ((char *)ra - a) == ((char *)rb - b)))
				pass++;
			else if (verbose)
				printf("  stop='%c' len=%zu 불일치\n", stops[si], lens[li]);
			li++;
		}
		si++;
	}
	printf("%d/%d\n", pass, total);
	return (pass != total);
}
