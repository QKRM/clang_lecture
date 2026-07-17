#include <stdio.h>
#include <stdlib.h>
#include "libsbs.h"

/*
 * sbs_split / sbs_free_split 단위 테스트.
 * grade.sh가 libsbs.a와 함께 빌드/실행한다.
 * 모두 통과하면 "SPLIT_OK" 출력 + 0 반환.
 */

static int	count(char **a)
{
	int	n;

	n = 0;
	while (a[n])
		n++;
	return (n);
}

int	main(void)
{
	char	**r;
	int		ok;

	ok = 1;

	/* 기본: 단어 3개 */
	r = sbs_split("echo hello world", ' ');
	if (count(r) != 3 || sbs_strcmp(r[0], "echo")
		|| sbs_strcmp(r[2], "world"))
		ok = 0;
	sbs_free_split(r);

	/* 연속·앞뒤 공백은 무시 → 단어 2개 */
	r = sbs_split("   a   b   ", ' ');
	if (count(r) != 2 || sbs_strcmp(r[0], "a") || sbs_strcmp(r[1], "b"))
		ok = 0;
	sbs_free_split(r);

	/* 빈 문자열 → 단어 0개 (배열 첫 칸이 NULL) */
	r = sbs_split("", ' ');
	if (count(r) != 0)
		ok = 0;
	sbs_free_split(r);

	/* 구분자만 있는 경우 → 단어 0개 */
	r = sbs_split("     ", ' ');
	if (count(r) != 0)
		ok = 0;
	sbs_free_split(r);

	/* 단어 1개 */
	r = sbs_split("solo", ' ');
	if (count(r) != 1 || sbs_strcmp(r[0], "solo"))
		ok = 0;
	sbs_free_split(r);

	if (ok)
	{
		printf("SPLIT_OK\n");
		return (0);
	}
	printf("SPLIT_FAIL\n");
	return (1);
}
