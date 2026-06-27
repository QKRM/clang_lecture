#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "libsbs.h"

/* strjoin: 두 문자열 연결 결과 + 독립 메모리. */
static int	one(char const *a, char const *b, const char *expected, int verbose)
{
	char	*r;
	int		ok;

	r = sbs_strjoin(a, b);
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
		printf("  strjoin(\"%s\",\"%s\") 기대 \"%s\"\n", a, b, expected);
	return (ok);
}

int	main(int argc, char **argv)
{
	int	pass;
	int	verbose;

	verbose = (argc > 1 && strcmp(argv[1], "-v") == 0);
	pass = 0;
	pass += one("Hello, ", "world!", "Hello, world!", verbose);
	pass += one("", "abc", "abc", verbose);
	pass += one("abc", "", "abc", verbose);
	pass += one("", "", "", verbose);
	pass += one("42", "seoul", "42seoul", verbose);
	printf("%d/5\n", pass);
	return (pass != 5);
}
