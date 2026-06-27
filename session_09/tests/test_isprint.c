#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include "libsbs.h"

int	main(int argc, char **argv)
{
	int	c;
	int	pass;
	int	verbose;

	verbose = (argc > 1 && strcmp(argv[1], "-v") == 0);
	pass = 0;
	c = 0;
	while (c <= 255)
	{
		if (!!sbs_isprint(c) == !!isprint(c))
			pass++;
		else if (verbose)
			printf("  입력 %d('%c'): 기대 %d, 실제 %d\n",
				c, (c >= 32 && c <= 126) ? c : ' ',
				!!isprint(c), !!sbs_isprint(c));
		c++;
	}
	printf("%d/256\n", pass);
	return (pass != 256);
}
