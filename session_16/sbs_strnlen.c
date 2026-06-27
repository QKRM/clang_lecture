#include "libsbs.h"

/*
 * 문자열 길이를 최대 maxlen까지만 센다.
 *  - '\0'을 만나거나 maxlen에 도달하면 멈춤
 *  - strlen과 달리 maxlen을 넘지 않아 안전
 */
size_t	sbs_strnlen(const char *s, size_t maxlen)
{
	size_t	len;

	len = 0;
	while (len < maxlen && s[len])
		len++;
	return (len);
}
