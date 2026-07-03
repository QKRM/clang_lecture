#include "libsbs.h"
#include <stdio.h>

/* 도전 2 예시 답안: argv로 "숫자 연산자 숫자" 형태를 받아 계산한다. */
int	main(int argc, char **argv)
{
	int	a;
	int	b;
	int	result;

	result = 0;
	if (argc != 4 || argv[2][1] != '\0')
	{
		printf("사용법: %s <숫자> <+|-|*|/> <숫자>\n", argv[0]);
		return (1);
	}
	a = sbs_atoi(argv[1]);
	b = sbs_atoi(argv[3]);
	if (sbs_strncmp(argv[2], "+", 1) == 0)
		result = a + b;
	else if (sbs_strncmp(argv[2], "-", 1) == 0)
		result = a - b;
	else if (sbs_strncmp(argv[2], "*", 1) == 0)
		result = a * b;
	else if (sbs_strncmp(argv[2], "/", 1) == 0)
	{
		if (b == 0)
		{
			printf("0으로 나눌 수 없습니다\n");
			return (1);
		}
		result = a / b;
	}
	else
	{
		printf("알 수 없는 연산자: %s\n", argv[2]);
		return (1);
	}
	printf("%d %s %d = %d\n", a, argv[2], b, result);
	return (0);
}
