#include "libsbs.h"

/* 9차시 sbs_tolower와 같은 원리. 13차시엔 그 파일이 없으므로 여기서 직접 변환(12차시 strcasecmp 컨벤션과 동일). */
static int	to_lower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	return (c);
}

char	*sbs_strcasestr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (little[0] == '\0')
		return ((char *)big);
	i = 0;
	while (big[i] && i < len)
	{
		j = 0;
		while (big[i + j] && i + j < len
			&& to_lower((unsigned char)big[i + j])
				== to_lower((unsigned char)little[j]))
			j++;
		if (little[j] == '\0')
			return ((char *)(big + i));
		i++;
	}
	return (NULL);
}
