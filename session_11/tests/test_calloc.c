#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "libsbs.h"

/* calloc: 0으로 초기화된 메모리 반환. 표준 calloc과 동작 비교. */
int	main(int argc, char **argv)
{
	int		pass;
	int		total;
	int		verbose;
	size_t	counts[] = {0, 1, 10, 100};
	size_t	sizes[] = {1, 4, 8};
	size_t	ci;
	size_t	si;

	verbose = (argc > 1 && strcmp(argv[1], "-v") == 0);
	pass = 0;
	total = 0;
	ci = 0;
	while (ci < 4)
	{
		si = 0;
		while (si < 3)
		{
			unsigned char	*p;
			size_t			n;
			size_t			k;
			int				ok;

			n = counts[ci] * sizes[si];
			p = (unsigned char *)sbs_calloc(counts[ci], sizes[si]);
			total++;
			ok = 1;
			/* 0개 요청이 아니면 포인터가 있어야 하고 전부 0이어야 함 */
			if (counts[ci] != 0 && sizes[si] != 0)
			{
				if (p == NULL)
					ok = 0;
				else
				{
					k = 0;
					while (k < n)
					{
						if (p[k] != 0)
							ok = 0;
						k++;
					}
				}
			}
			if (ok)
				pass++;
			else if (verbose)
				printf("  count=%zu size=%zu 불일치\n", counts[ci], sizes[si]);
			free(p);
			si++;
		}
		ci++;
	}
	printf("%d/%d\n", pass, total);
	return (pass != total);
}
