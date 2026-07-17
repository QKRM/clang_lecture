#include <stdio.h>
#include <stdlib.h>
#include "libsbs.h"

/*
 * wordinfo — libsbs.a를 링크해서 쓰는 첫 프로그램.
 *
 * 실행 예:
 *   $ ./wordinfo hello C99
 *
 * 표준 라이브러리의 strlen/toupper/isalpha/strdup 대신
 * 우리가 9~14차시에 직접 만든 sbs_ 버전을 쓴다.
 * 라이브러리(libsbs.a)와 프로그램(main.c)이 분리돼 있다는 점이 핵심.
 */

static void	print_upper(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		printf("%c", sbs_toupper((unsigned char)s[i]));
		i++;
	}
}

static int	all_alpha(const char *s)
{
	int	i;

	if (s[0] == '\0')
		return (0);
	i = 0;
	while (s[i])
	{
		if (!sbs_isalpha((unsigned char)s[i]))
			return (0);
		i++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	int		i;
	char	*copy;

	if (argc < 2)
	{
		printf("사용법: ./wordinfo 단어 [단어...]\n");
		return (1);
	}
	i = 1;
	while (i < argc)
	{
		copy = sbs_strdup(argv[i]);
		if (copy == NULL)
			return (1);
		printf("[%s]\n", copy);
		printf("  길이   : %zu\n", sbs_strlen(copy));
		printf("  대문자 : ");
		print_upper(copy);
		printf("\n");
		if (all_alpha(copy))
			printf("  알파벳 : 예\n");
		else
			printf("  알파벳 : 아니오\n");
		free(copy);
		i++;
	}
	return (0);
}
