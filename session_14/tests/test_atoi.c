#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "libsbs.h"

/* 표준 atoi를 정답으로. 부호/공백/숫자 처리. */
int	main(int argc, char **argv)
{
	int		pass;
	int		total;
	int		verbose;
	char	*cases[] = {
	"42", "-42", "+42", "   123", "\t-7", "0", "  +0", "abc",
	"12ab", "  -99x", "2147483647", "-2147483648", "", "   ", "+-5"
	};
	int		i;

	verbose = (argc > 1 && strcmp(argv[1], "-v") == 0);
	pass = 0;
	total = 0;
	i = 0;
	while (i < 15)
	{
		int ra = atoi(cases[i]);
		int rb = sbs_atoi(cases[i]);
		total++;
		if (ra == rb)
			pass++;
		else if (verbose)
			printf("  \"%s\": 기대 %d, 실제 %d\n", cases[i], ra, rb);
		i++;
	}
	printf("%d/%d\n", pass, total);
	return (pass != total);
}
