#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include "libsbs.h"

/* 표준 isalpha를 정답(oracle)으로 사용. 0~255 전 범위 비교. */
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
		if (!!sbs_isalpha(c) == !!isalpha(c))
			pass++;
		else if (verbose)
			printf("  입력 %d('%c'): 기대 %d, 실제 %d\n",
				c, (c >= 32 && c <= 126) ? c : ' ',
				!!isalpha(c), !!sbs_isalpha(c));
		c++;
	}
	printf("%d/256\n", pass);
	return (pass != 256);
}
