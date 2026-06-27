#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "libsbs.h"

/* strdup: 내용 일치 + 독립 메모리(원본과 다른 주소) + free 가능. */
int	main(int argc, char **argv)
{
	int		pass;
	int		total;
	int		verbose;
	char	*cases[] = {"", "a", "hello world", "42 seoul", "\t\n mixed"};
	int		i;

	verbose = (argc > 1 && strcmp(argv[1], "-v") == 0);
	pass = 0;
	total = 0;
	i = 0;
	while (i < 5)
	{
		char	*dup;
		int		ok;

		dup = sbs_strdup(cases[i]);
		total++;
		ok = 1;
		if (dup == NULL)
			ok = 0;
		else
		{
			if (strcmp(dup, cases[i]) != 0)
				ok = 0;
			if (dup == cases[i])
				ok = 0;
			free(dup);
		}
		if (ok)
			pass++;
		else if (verbose)
			printf("  \"%s\" 불일치\n", cases[i]);
		i++;
	}
	printf("%d/%d\n", pass, total);
	return (pass != total);
}
