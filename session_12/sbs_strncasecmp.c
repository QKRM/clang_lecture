#include "libsbs.h"

/*
 * 두 문자열을 대소문자 구분 없이 최대 n글자까지 비교한다.
 *  - n글자 안에서 처음 다른 글자의 차이를 반환 (소문자 기준)
 *  - n글자까지 같으면 0
 *  - strcasecmp의 길이 제한 버전 (14차시 strncmp와 같은 구조)
 */
static int	to_lower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	return (c);
}

int	sbs_strncasecmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && (s1[i] || s2[i]))
	{
		if (to_lower((unsigned char)s1[i]) != to_lower((unsigned char)s2[i]))
			return (to_lower((unsigned char)s1[i])
				- to_lower((unsigned char)s2[i]));
		i++;
	}
	return (0);
}
