#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "libsbs.h"

/*
 * 종합 통합 테스트: libsbs.a를 링크해 26개 함수를 대표값으로 검증.
 * grade.sh가 이 파일을 libsbs.a와 함께 빌드/실행한다.
 * 모든 검사를 통과하면 "ALL_OK" 출력 + 0 반환.
 */

static int	g_fail;

static void	check(int cond, const char *name)
{
	if (!cond)
	{
		printf("  [FAIL] %s\n", name);
		g_fail++;
	}
}

static int	sign(int x)
{
	if (x > 0)
		return (1);
	if (x < 0)
		return (-1);
	return (0);
}

int	main(void)
{
	char	buf[32];
	char	*p;

	g_fail = 0;

	/* 9차시 — 문자 분류/변환 */
	check(sbs_isalpha('A') && !sbs_isalpha('5'), "isalpha");
	check(sbs_isdigit('7') && !sbs_isdigit('x'), "isdigit");
	check(sbs_isalnum('a') && sbs_isalnum('9') && !sbs_isalnum(' '), "isalnum");
	check(sbs_isascii(0) && sbs_isascii(127) && !sbs_isascii(200), "isascii");
	check(sbs_isprint(' ') && !sbs_isprint(127), "isprint");
	check(sbs_toupper('a') == 'A' && sbs_toupper('5') == '5', "toupper");
	check(sbs_tolower('Z') == 'z' && sbs_tolower('5') == '5', "tolower");

	/* 10차시 — 메모리 */
	sbs_memset(buf, 'x', 5);
	check(buf[0] == 'x' && buf[4] == 'x', "memset");
	sbs_bzero(buf, 5);
	check(buf[0] == 0 && buf[4] == 0, "bzero");
	sbs_memcpy(buf, "hello", 6);
	check(memcmp(buf, "hello", 6) == 0, "memcpy");
	check(sbs_memccpy(buf, "abcd", 'c', 4) != NULL, "memccpy");
	check(sbs_memchr("hello", 'l', 5) != NULL && sbs_memchr("hello", 'z', 5) == NULL, "memchr");
	check(sign(sbs_memcmp("abc", "abd", 3)) < 0 && sbs_memcmp("abc", "abc", 3) == 0, "memcmp");

	/* 11차시 — 동적 메모리 */
	p = (char *)sbs_calloc(4, 2);
	check(p != NULL && p[0] == 0 && p[7] == 0, "calloc");
	free(p);
	p = sbs_substr("hello world", 6, 5);
	check(p != NULL && strcmp(p, "world") == 0, "substr");
	free(p);
	p = sbs_strjoin("Hello, ", "world!");
	check(p != NULL && strcmp(p, "Hello, world!") == 0, "strjoin");
	free(p);
	p = sbs_itoa(-2147483648);
	check(p != NULL && strcmp(p, "-2147483648") == 0, "itoa");
	free(p);
	p = sbs_strdup("libsbs");
	check(p != NULL && strcmp(p, "libsbs") == 0 && p != (char *)"libsbs", "strdup");
	free(p);

	/* 12차시 — 문자열 I */
	check(sbs_strlen("hello") == 5 && sbs_strlen("") == 0, "strlen");
	sbs_strlcpy(buf, "hi", 32);
	check(strcmp(buf, "hi") == 0, "strlcpy");
	sbs_strlcat(buf, "!!", 32);
	check(strcmp(buf, "hi!!") == 0, "strlcat");

	/* 13차시 — 문자열 II */
	check(sbs_strchr("hello", 'e') != NULL && sbs_strchr("hello", 'z') == NULL, "strchr");
	{
		const char	*hl = "hello";
		check(sbs_strrchr(hl, 'l') == hl + 3, "strrchr");
	}
	check(sbs_strnstr("hello world", "world", 11) != NULL
		&& sbs_strnstr("hello", "xyz", 5) == NULL, "strnstr");

	/* 14차시 — 비교/변환 */
	check(sbs_strncmp("abc", "abc", 3) == 0 && sign(sbs_strncmp("abc", "abd", 3)) < 0, "strncmp");
	check(sbs_atoi("  -42") == -42 && sbs_atoi("12ab") == 12 && sbs_atoi("abc") == 0, "atoi");

	if (g_fail == 0)
	{
		printf("ALL_OK\n");
		return (0);
	}
	printf("FAILED: %d\n", g_fail);
	return (1);
}
