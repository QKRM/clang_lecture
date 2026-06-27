#include <string.h>
#include <stdio.h>
#include "libsbs.h"

/* 표준 strlen을 정답으로. */
int	main(int argc, char **argv)
{
	int		pass;
	int		total;
	int		verbose;
	char	*cases[] = {"", "a", "hello", "42 seoul gajwa", "\t\n  "};
	int		i;

	verbose = (argc > 1 && strcmp(argv[1], "-v") == 0);
	pass = 0;
	total = 0;
	i = 0;
	while (i < 5)
	{
		total++;
		if (sbs_strlen(cases[i]) == strlen(cases[i]))
			pass++;
		else if (verbose)
			printf("  \"%s\": 기대 %zu, 실제 %zu\n",
				cases[i], strlen(cases[i]), sbs_strlen(cases[i]));
		i++;
	}
	printf("%d/%d\n", pass, total);
	return (pass != total);
}
