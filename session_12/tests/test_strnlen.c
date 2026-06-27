#include <string.h>
#include <stdio.h>
#include "libsbs.h"

/* 표준 strnlen을 정답으로. */
int	main(int argc, char **argv)
{
	int		pass;
	int		total;
	int		verbose;
	char	*cases[] = {"", "a", "hello", "42 seoul"};
	size_t	maxs[] = {0, 1, 3, 5, 100};
	int		ci;
	size_t	mi;

	verbose = (argc > 1 && strcmp(argv[1], "-v") == 0);
	pass = 0;
	total = 0;
	ci = 0;
	while (ci < 4)
	{
		mi = 0;
		while (mi < 5)
		{
			total++;
			if (sbs_strnlen(cases[ci], maxs[mi]) == strnlen(cases[ci], maxs[mi]))
				pass++;
			else if (verbose)
				printf("  \"%s\" max=%zu 불일치\n", cases[ci], maxs[mi]);
			mi++;
		}
		ci++;
	}
	printf("%d/%d\n", pass, total);
	return (pass != total);
}
