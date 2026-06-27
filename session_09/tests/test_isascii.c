#include <stdio.h>
#include <string.h>
#include "libsbs.h"

/* isascii는 일부 환경에서 헤더가 다르므로 정답을 직접 정의: 0~127이 ascii */
static int	oracle_isascii(int c)
{
	return (c >= 0 && c <= 127);
}

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
		if (!!sbs_isascii(c) == !!oracle_isascii(c))
			pass++;
		else if (verbose)
			printf("  입력 %d: 기대 %d, 실제 %d\n",
				c, !!oracle_isascii(c), !!sbs_isascii(c));
		c++;
	}
	printf("%d/256\n", pass);
	return (pass != 256);
}
