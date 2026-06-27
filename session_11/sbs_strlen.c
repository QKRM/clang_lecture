#include "libsbs.h"

/* 12차시에서 정식으로 다룸. 여기서는 substr/strjoin이 길이 계산에 사용. */
size_t	sbs_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}
