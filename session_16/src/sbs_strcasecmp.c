#include "libsbs.h"

/*
 * 두 문자열을 대소문자 구분 없이 끝까지 비교한다.
 *  - 각 글자를 소문자로 바꿔 비교 ('A'~'Z' → +32)
 *  - 처음 다른 글자에서 차이를 반환 (부호가 의미)
 *  - 둘 다 끝까지 같으면 0
 *  - 9차시 tolower와 같은 원리 (여기선 의존 없이 직접 변환)
 */
static int	to_lower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	return (c);
}

int	sbs_strcasecmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (to_lower((unsigned char)s1[i]) != to_lower((unsigned char)s2[i]))
			return (to_lower((unsigned char)s1[i])
				- to_lower((unsigned char)s2[i]));
		i++;
	}
	return (0);
}
