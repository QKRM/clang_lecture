#include <string.h>
#include <stdio.h>
#include "libsbs.h"

/* 표준 memcmp를 정답(oracle)으로. 부호(sign)만 비교 — 크기가 아니라 방향이 같으면 정답. */
static int	sgn(int x)
{
	return ((x > 0) - (x < 0));
}

int	main(int argc, char **argv)
{
	int				pass;
	int				total;
	int				verbose;
	unsigned char	A[5][8] = {
		{'h', 'e', 'l', 'l', 'o', 0, 0, 0},
		{'h', 'e', 'l', 'l', 'o', 0, 0, 0},
		{'a', 'b', 'c', 0, 0, 0, 0, 0},
		{'a', 'b', 'd', 0, 0, 0, 0, 0},
		{0xff, 0x01, 0x00, 0, 0, 0, 0, 0},
	};
	unsigned char	B[5][8] = {
		{'h', 'e', 'l', 'l', 'o', 0, 0, 0},
		{'w', 'o', 'r', 'l', 'd', 0, 0, 0},
		{'a', 'b', 'd', 0, 0, 0, 0, 0},
		{'a', 'b', 'c', 0, 0, 0, 0, 0},
		{0x01, 0xff, 0x00, 0, 0, 0, 0, 0},
	};
	size_t			lens[] = {0, 1, 2, 3, 5};
	int				ci;
	size_t			li;

	verbose = (argc > 1 && strcmp(argv[1], "-v") == 0);
	pass = 0;
	total = 0;
	ci = 0;
	while (ci < 5)
	{
		li = 0;
		while (li < 5)
		{
			int ra = memcmp(A[ci], B[ci], lens[li]);
			int rb = sbs_memcmp(A[ci], B[ci], lens[li]);
			total++;
			if (sgn(ra) == sgn(rb))
				pass++;
			else if (verbose)
				printf("  case=%d len=%zu 불일치 (std=%d sbs=%d)\n",
					ci, lens[li], ra, rb);
			li++;
		}
		ci++;
	}
	printf("%d/%d\n", pass, total);
	return (pass != total);
}
