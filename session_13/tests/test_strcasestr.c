#include <string.h>
#include <stdio.h>
#include "libsbs.h"

/*
 * strcasestr 정답 동작 (oracle):
 *  - big에서 little을 대소문자 무시하고 len바이트 범위 안에서 검색
 *  - little이 빈 문자열이면 big 반환
 *  - 찾으면 시작 위치, 못 찾으면 NULL
 */
static int	oracle_lower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	return (c);
}

static char	*oracle_strcasestr(const char *big, const char *little, size_t len)
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
			&& oracle_lower((unsigned char)big[i + j])
				== oracle_lower((unsigned char)little[j]))
			j++;
		if (little[j] == '\0')
			return ((char *)(big + i));
		i++;
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	int		pass;
	int		total;
	int		verbose;
	char	*big = "Hello, This Is A Simple TEST string";
	char	*needles[] = {"", "hello", "IS", "test", "xyz", "STRING", "is a si"};
	size_t	lens[] = {0, 5, 10, 20, 36, 100};
	int		ni;
	size_t	li;

	verbose = (argc > 1 && strcmp(argv[1], "-v") == 0);
	pass = 0;
	total = 0;
	ni = 0;
	while (ni < 7)
	{
		li = 0;
		while (li < 6)
		{
			char *ra = oracle_strcasestr(big, needles[ni], lens[li]);
			char *rb = sbs_strcasestr(big, needles[ni], lens[li]);
			total++;
			if (ra == rb)
				pass++;
			else if (verbose)
				printf("  needle=\"%s\" len=%zu 불일치\n", needles[ni], lens[li]);
			li++;
		}
		ni++;
	}
	printf("%d/%d\n", pass, total);
	return (pass != total);
}
