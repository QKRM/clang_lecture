#include <string.h>
#include <stdio.h>
#include "libsbs.h"

/* 표준 memset을 정답(oracle)으로. 버퍼 내용 + 반환 포인터 비교. */
int	main(int argc, char **argv)
{
	char	a[64];
	char	b[64];
	int		pass;
	int		total;
	int		verbose;
	size_t	lens[] = {0, 1, 5, 32, 64};
	int		vals[] = {0, 'A', 42, 255};
	size_t	li;
	int		vi;

	verbose = (argc > 1 && strcmp(argv[1], "-v") == 0);
	pass = 0;
	total = 0;
	li = 0;
	while (li < 5)
	{
		vi = 0;
		while (vi < 4)
		{
			memset(a, 0x7f, 64);
			memset(b, 0x7f, 64);
			void *ra = memset(a, vals[vi], lens[li]);
			void *rb = sbs_memset(b, vals[vi], lens[li]);
			total++;
			if (memcmp(a, b, 64) == 0 && ra == a && rb == b)
				pass++;
			else if (verbose)
				printf("  len=%zu val=%d 불일치\n", lens[li], vals[vi]);
			vi++;
		}
		li++;
	}
	printf("%d/%d\n", pass, total);
	return (pass != total);
}
