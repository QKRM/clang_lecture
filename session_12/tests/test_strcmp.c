#include <string.h>
#include <stdio.h>
#include "libsbs.h"

/* 표준 strcmp를 정답으로. 부호(양/음/0)만 비교. */
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
	{"abc", "ab"}, {"ab", "abc"}, {"", ""}, {"", "a"},
	{"\xff", "\x01"}
	};
	int		i;

	verbose = (argc > 1 && strcmp(argv[1], "-v") == 0);
	pass = 0;
	total = 0;
	i = 0;
	while (i < 8)
	{
		int ra = strcmp(pairs[i][0], pairs[i][1]);
		int rb = sbs_strcmp(pairs[i][0], pairs[i][1]);
		total++;
		if (sign(ra) == sign(rb))
			pass++;
		else if (verbose)
			printf("  \"%s\" vs \"%s\" 부호 %d/%d\n",
				pairs[i][0], pairs[i][1], sign(ra), sign(rb));
		i++;
	}
	printf("%d/%d\n", pass, total);
	return (pass != total);
}
