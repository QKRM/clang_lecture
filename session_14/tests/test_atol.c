#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "libsbs.h"

/* 표준 atol을 정답으로. int 범위를 넘는 큰 수까지 확인. */
int	main(int argc, char **argv)
{
	int		pass;
	int		total;
	int		verbose;
	char	*cases[] = {
	"42", "-42", "+42", "   123", "\t-7", "0", "  +0", "abc",
	"12ab", "  -99x", "9999999999", "-9999999999", "", "   ", "+-5"
	};
	int		i;

	verbose = (argc > 1 && strcmp(argv[1], "-v") == 0);
	pass = 0;
	total = 0;
	i = 0;
	while (i < 15)
	{
		long ra = atol(cases[i]);
		long rb = sbs_atol(cases[i]);
		total++;
		if (ra == rb)
			pass++;
		else if (verbose)
			printf("  \"%s\": 기대 %ld, 실제 %ld\n", cases[i], ra, rb);
		i++;
	}
	printf("%d/%d\n", pass, total);
	return (pass != total);
}
