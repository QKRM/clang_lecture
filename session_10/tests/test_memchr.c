#include <string.h>
#include <stdio.h>
#include "libsbs.h"

/* 표준 memchr을 정답(oracle)으로. 반환 포인터(찾은 위치 / NULL) 비교. */
int	main(int argc, char **argv)
{
	char	buf[16] = "hello world";
	int		pass;
	int		total;
	int		verbose;
	int		needles[] = {'h', 'o', 'd', 'z', 0};
	size_t	lens[] = {0, 1, 5, 11, 12};
	int		ni;
	size_t	li;

	verbose = (argc > 1 && strcmp(argv[1], "-v") == 0);
	pass = 0;
	total = 0;
	ni = 0;
	while (ni < 5)
	{
		li = 0;
		while (li < 5)
		{
			void *ra = memchr(buf, needles[ni], lens[li]);
			void *rb = sbs_memchr(buf, needles[ni], lens[li]);
			total++;
			if (ra == rb)
				pass++;
			else if (verbose)
				printf("  needle=%d len=%zu 불일치\n", needles[ni], lens[li]);
			li++;
		}
		ni++;
	}
	printf("%d/%d\n", pass, total);
	return (pass != total);
}
