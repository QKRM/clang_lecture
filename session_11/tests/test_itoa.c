#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "libsbs.h"

/* itoa: int → 문자열. 0/음수/INT_MIN/INT_MAX 포함. */
static int	one(int n, const char *expected, int verbose)
{
	char	*r;
	int		ok;

	r = sbs_itoa(n);
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
		printf("  itoa(%d) 기대 \"%s\"\n", n, expected);
	return (ok);
}

int	main(int argc, char **argv)
{
	int	pass;
	int	verbose;

	verbose = (argc > 1 && strcmp(argv[1], "-v") == 0);
	pass = 0;
	pass += one(0, "0", verbose);
	pass += one(42, "42", verbose);
	pass += one(-42, "-42", verbose);
	pass += one(123456, "123456", verbose);
	pass += one(2147483647, "2147483647", verbose);
	pass += one(-2147483648, "-2147483648", verbose);
	printf("%d/6\n", pass);
	return (pass != 6);
}
