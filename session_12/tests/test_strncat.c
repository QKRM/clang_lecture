#include <string.h>
#include <stdio.h>
#include "libsbs.h"

/* 표준 strncat을 정답으로. 결과 문자열 + 반환 포인터 비교. */
int	main(int argc, char **argv)
{
	int		pass;
	int		total;
	int		verbose;
	char	*inits[] = {"", "ab", "Hello"};
	char	*srcs[] = {"", "XY", "world"};
	size_t	ns[] = {0, 1, 3, 10};
	int		ii;
	int		si;
	size_t	ni;

	verbose = (argc > 1 && strcmp(argv[1], "-v") == 0);
	pass = 0;
	total = 0;
	ii = 0;
	while (ii < 3)
	{
		si = 0;
		while (si < 3)
		{
			ni = 0;
			while (ni < 4)
			{
				char	a[32];
				char	b[32];
				memset(a, 0, 32);
				memset(b, 0, 32);
				strcpy(a, inits[ii]);
				strcpy(b, inits[ii]);
				char *ra = strncat(a, srcs[si], ns[ni]);
				char *rb = sbs_strncat(b, srcs[si], ns[ni]);
				total++;
				if (strcmp(a, b) == 0 && ra == a && rb == b)
					pass++;
				else if (verbose)
					printf("  init=\"%s\" src=\"%s\" n=%zu 불일치\n",
						inits[ii], srcs[si], ns[ni]);
				ni++;
			}
			si++;
		}
		ii++;
	}
	printf("%d/%d\n", pass, total);
	return (pass != total);
}
