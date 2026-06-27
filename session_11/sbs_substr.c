#include "libsbs.h"
#include <stdlib.h>

/*
 * 문자열 s의 start 위치부터 최대 len글자를 잘라 새 메모리에 복제.
 *  - s가 NULL이면 NULL
 *  - start가 문자열 길이 이상이면 빈 문자열("") 반환
 *  - len이 남은 길이보다 크면 남은 길이까지만
 *  - 반환 메모리는 호출자가 free
 */
char	*sbs_substr(char const *s, unsigned int start, size_t len)
{
	size_t	slen;
	size_t	i;
	char	*sub;

	if (s == NULL)
		return (NULL);
	slen = sbs_strlen(s);
	if (start >= slen)
		len = 0;
	else if (len > slen - start)
		len = slen - start;
	sub = (char *)malloc(len + 1);
	if (sub == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}
