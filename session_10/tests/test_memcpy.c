#include <string.h>
#include <stdio.h>
#include "libsbs.h"

/* 표준 memcpy를 정답으로. 복사 결과 + 반환 포인터 비교. */
int	main(int argc, char **argv)
{
	char		src[64];
	char		a[64];
	char		b[64];
	int			pass;
	int			total;
	int			verbose;
	size_t		lens[] = {0, 1, 7, 32, 64};
	size_t		li;
	size_t		k;

	verbose = (argc > 1 && strcmp(argv[1], "-v") == 0);
	k = 0;
	while (k < 64)
	{
		src[k] = (char)(k + 1);
		k++;
	}
	pass = 0;
	total = 0;
	li = 0;
	while (li < 5)
	{
		memset(a, 0, 64);
		memset(b, 0, 64);
		void *ra = memcpy(a, src, lens[li]);
		void *rb = sbs_memcpy(b, src, lens[li]);
		total++;
		if (memcmp(a, b, 64) == 0 && ra == a && rb == b)
			pass++;
		else if (verbose)
			printf("  len=%zu 불일치\n", lens[li]);
		li++;
	}
	printf("%d/%d\n", pass, total);
	return (pass != total);
}
