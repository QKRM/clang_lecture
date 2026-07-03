#include "libsbs.h"
#include <stdio.h>

/* 도전 1 예시 답안: '.'로 구분된 버전 문자열을 부분별로 sbs_atoi 변환해 비교한다. */
static int	next_part(const char *s, int *idx)
{
	int	start;
	int	value;

	start = *idx;
	while (s[*idx] && s[*idx] != '.')
		(*idx)++;
	value = sbs_atoi(s + start);
	if (s[*idx] == '.')
		(*idx)++;
	return (value);
}

static int	compare_version(const char *a, const char *b)
{
	int	ia;
	int	ib;
	int	va;
	int	vb;

	ia = 0;
	ib = 0;
	while (a[ia] || b[ib])
	{
		va = next_part(a, &ia);
		vb = next_part(b, &ib);
		if (va != vb)
			return (va - vb);
	}
	return (0);
}

int	main(void)
{
	char	*v1;
	char	*v2;
	int		cmp;

	v1 = "1.2.3";
	v2 = "1.10.0";
	cmp = compare_version(v1, v2);
	if (cmp < 0)
		printf("%s < %s\n", v1, v2);
	else if (cmp > 0)
		printf("%s > %s\n", v1, v2);
	else
		printf("%s == %s\n", v1, v2);
	return (0);
}
