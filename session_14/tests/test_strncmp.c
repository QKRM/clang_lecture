#include <string.h>
#include <stdio.h>
#include "libsbs.h"

/* 표준 strncmp를 정답으로. 부호만 비교. */
static int	sign(int x)
{
	if (x > 0)
		return (1);
	if (x < 0)
		return (-1);
	return (0);
}

int	main(int argc, char **argv)
{
	int		pass;
	int		total;
	int		verbose;
	char	*pairs[][2] = {
	{"hello", "hello"}, {"hello", "world"}, {"abc", "abd"},
	{"abc", "ab"}, {"ab", "abc"}, {"", ""}, {"test", "test!"}
	};
	size_t	lens[] = {0, 1, 3, 5, 10};
	int		pi;
	size_t	li;

	verbose = (argc > 1 && strcmp(argv[1], "-v") == 0);
	pass = 0;
	total = 0;
	pi = 0;
	while (pi < 7)
	{
		li = 0;
		while (li < 5)
		{
			int ra = strncmp(pairs[pi][0], pairs[pi][1], lens[li]);
			int rb = sbs_strncmp(pairs[pi][0], pairs[pi][1], lens[li]);
			total++;
			if (sign(ra) == sign(rb))
				pass++;
			else if (verbose)
				printf("  \"%s\" vs \"%s\" n=%zu 부호 %d/%d\n",
					pairs[pi][0], pairs[pi][1], lens[li], sign(ra), sign(rb));
			li++;
		}
		pi++;
	}
	printf("%d/%d\n", pass, total);
	return (pass != total);
}
