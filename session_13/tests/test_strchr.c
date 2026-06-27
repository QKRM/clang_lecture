#include <string.h>
#include <stdio.h>
#include "libsbs.h"

/* 표준 strchr를 정답으로. \0 검색 포함. */
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
		char *ra = strchr(s, targets[i]);
		char *rb = sbs_strchr(s, targets[i]);
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
