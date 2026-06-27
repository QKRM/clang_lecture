#include "libsbs.h"

/*
 * dst의 기존 문자열 뒤에 src를 최대 n글자 이어붙인다.
 *  - 항상 '\0'로 끝맺는다 (표준 strncat 동작)
 *  - dst를 반환
 */
char	*sbs_strncat(char *dst, const char *src, size_t n)
{
	size_t	dstlen;
	size_t	i;

	dstlen = 0;
	while (dst[dstlen])
		dstlen++;
	i = 0;
	while (i < n && src[i])
	{
		dst[dstlen + i] = src[i];
		i++;
	}
	dst[dstlen + i] = '\0';
	return (dst);
}
