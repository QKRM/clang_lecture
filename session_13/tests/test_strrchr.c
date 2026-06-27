#include <string.h>
#include <stdio.h>
#include "libsbs.h"

/* 표준 strrchr를 정답으로. 역방향 검색 + \0. */
int	main(int argc, char **argv)
{
	int		pass;
	int		total;
	int		verbose;
	char	*s = "hello world";
	int		targets[] = {'h', 'o', 'd', 'z', 'l', '\0'};
	int		i;

	verbose = (argc > 1 && strcmp(argv[1], "-v") == 0);
	pass = 0;
	total = 0;
	i = 0;
	while (i < 6)
	{
		char *ra = strrchr(s, targets[i]);
		char *rb = sbs_strrchr(s, targets[i]);
		total++;
		if (ra == rb)
			pass++;
		else if (verbose)
			printf("  c='%c'(%d) 불일치\n", targets[i], targets[i]);
		i++;
	}
	printf("%d/%d\n", pass, total);
	return (pass != total);
}
