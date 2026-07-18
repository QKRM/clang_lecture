#include "libsbs.h"
#include <stdlib.h>

/*
 * 두 문자열 s1, s2를 이어붙여 새 메모리에 만든다.
 *  - s1 또는 s2가 NULL이면 NULL
 *  - 새 메모리 크기 = len(s1) + len(s2) + 1(\0)
 *  - 반환 메모리는 호출자가 free
 */
char	*sbs_strjoin(char const *s1, char const *s2)
{
	size_t	l1;
	size_t	l2;
	size_t	i;
	size_t	j;
	char	*res;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	l1 = sbs_strlen(s1);
	l2 = sbs_strlen(s2);
	res = (char *)malloc(l1 + l2 + 1);
	if (res == NULL)
		return (NULL);
	i = 0;
	while (i < l1)
	{
		res[i] = s1[i];
		i++;
	}
	j = 0;
	while (j < l2)
	{
		res[i + j] = s2[j];
		j++;
	}
	res[i + j] = '\0';
	return (res);
}
