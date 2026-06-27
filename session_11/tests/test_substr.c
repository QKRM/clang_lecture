#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "libsbs.h"

/* substr: 내용 일치 + 독립 메모리 + 엣지(start 초과, len 초과). */
static int	one(char const *s, unsigned int start, size_t len,
			const char *expected, int verbose)
{
	char	*r;
	int		ok;

	r = sbs_substr(s, start, len);
	ok = 1;
	if (r == NULL)
		ok = 0;
	else
	{
		if (strcmp(r, expected) != 0)
			ok = 0;
		free(r);
	}
	if (!ok && verbose)
		printf("  substr(\"%s\",%u,%zu) 기대 \"%s\"\n", s, start, len, expected);
	return (ok);
}

int	main(int argc, char **argv)
{
	int	pass;
	int	verbose;

	verbose = (argc > 1 && strcmp(argv[1], "-v") == 0);
	pass = 0;
	pass += one("hello world", 0, 5, "hello", verbose);
	pass += one("hello world", 6, 5, "world", verbose);
	pass += one("hello", 0, 100, "hello", verbose);
	pass += one("hello", 3, 100, "lo", verbose);
	pass += one("hello", 10, 5, "", verbose);
	pass += one("hello", 2, 0, "", verbose);
	printf("%d/6\n", pass);
	return (pass != 6);
}
