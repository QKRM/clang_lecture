#include "libsbs.h"

/*
 * 두 문자열을 끝까지 비교한다 (길이 제한 없음).
 *  - 처음 다른 글자에서 차이를 반환 (부호가 의미)
 *  - 둘 다 '\0'까지 같으면 0
 *  - unsigned char로 비교해야 부호가 정확 (14차시 strncmp와 같은 이유)
 */
int	sbs_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
