#include <stdio.h>
#include <stdlib.h>
#include "libsbs.h"

/*
 * libsbs.a를 링크해 함수가 실제로 동작하는지 확인하는 프로그램.
 * grade.sh가 이 파일을 libsbs.a와 함께 컴파일/링크/실행한다.
 */
int	main(void)
{
	char	*dup;
	int		ok;

	ok = 1;
	if (sbs_isalpha('A') == 0)
		ok = 0;
	if (sbs_isalpha('5') != 0)
		ok = 0;
	if (sbs_toupper('a') != 'A')
		ok = 0;
	if (sbs_strlen("hello") != 5)
		ok = 0;
	dup = sbs_strdup("libsbs");
	if (dup == NULL || sbs_strlen(dup) != 6)
		ok = 0;
	free(dup);
	if (sbs_strcmp("exit", "exit") != 0)
		ok = 0;
	if (sbs_strcmp("exit", "quit") == 0)
		ok = 0;
	if (ok)
	{
		printf("LINK_OK\n");
		return (0);
	}
	printf("LINK_FAIL\n");
	return (1);
}
