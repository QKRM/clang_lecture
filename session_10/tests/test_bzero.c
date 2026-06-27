#include <strings.h>
#include <string.h>
#include <stdio.h>
#include "libsbs.h"

/* 표준 bzero를 정답으로. 0으로 채워졌는지 비교. */
int	main(int argc, char **argv)
{
	char	a[64];
	char	b[64];
	int		pass;
	int		total;
	int		verbose;
	size_t	lens[] = {0, 1, 10, 64};
	size_t	li;

	verbose = (argc > 1 && strcmp(argv[1], "-v") == 0);
	pass = 0;
	total = 0;
	li = 0;
	while (li < 4)
	{
		memset(a, 0x7f, 64);
		memset(b, 0x7f, 64);
		bzero(a, lens[li]);
		sbs_bzero(b, lens[li]);
		total++;
		if (memcmp(a, b, 64) == 0)
			pass++;
		else if (verbose)
			printf("  len=%zu 불일치\n", lens[li]);
		li++;
	}
	printf("%d/%d\n", pass, total);
	return (pass != total);
}
