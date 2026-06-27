#include "libsbs.h"

/*
 * src를 dst로 최대 n글자 복사한다.
 *  - src가 n보다 짧으면 남는 칸을 '\0'으로 채운다 (표준 strncpy 동작)
 *  - src가 n 이상이면 dst는 '\0'로 끝나지 않을 수 있다 (주의)
 *  - dst를 반환
 */
char	*sbs_strncpy(char *dst, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dst[i] = '\0';
		i++;
	}
	return (dst);
}
