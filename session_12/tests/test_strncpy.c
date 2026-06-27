#include <string.h>
#include <stdio.h>
#include "libsbs.h"

/* 표준 strncpy를 정답으로. 버퍼 내용(패딩 포함) + 반환 포인터 비교. */
int	main(int argc, char **argv)
{
	int		pass;
	int		total;
	int		verbose;
	char	*srcs[] = {"", "hi", "hello"};
	size_t	ns[] = {0, 1, 3, 5, 8};
	int		si;
	size_t	ni;

	verbose = (argc > 1 && strcmp(argv[1], "-v") == 0);
	pass = 0;
	total = 0;
	si = 0;
	while (si < 3)
	{
		ni = 0;
		while (ni < 5)
		{
			char	a[16];
			char	b[16];
			memset(a, 1, 16);
			memset(b, 1, 16);
			char *ra = strncpy(a, srcs[si], ns[ni]);
			char *rb = sbs_strncpy(b, srcs[si], ns[ni]);
			total++;
			if (memcmp(a, b, 16) == 0 && ra == a && rb == b)
				pass++;
			else if (verbose)
				printf("  src=\"%s\" n=%zu 불일치\n", srcs[si], ns[ni]);
			ni++;
		}
		si++;
	}
	printf("%d/%d\n", pass, total);
	return (pass != total);
}
