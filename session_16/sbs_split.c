#include "libsbs.h"
#include <stdlib.h>

/*
 * 문자열 s를 구분자 c로 쪼개 단어 배열(char **)을 만든다.
 *  - 연속된 구분자는 하나로 취급, 앞뒤 구분자는 무시
 *  - 마지막 원소는 NULL (끝 표시)
 *  - 각 단어와 배열 모두 malloc → sbs_free_split으로 해제
 *  - s가 NULL이면 NULL
 * 예) sbs_split("  echo   hi ", ' ') → {"echo", "hi", NULL}
 */

/* 구분자로 나뉜 '단어'가 몇 개인지 센다 */
static size_t	count_words(const char *s, char c)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (count);
}

/* 실패 시 지금까지 만든 단어 n개 + 배열을 해제하고 NULL 반환용 정리 */
static void	free_partial(char **arr, size_t n)
{
	while (n > 0)
		free(arr[--n]);
	free(arr);
}

char	**sbs_split(const char *s, char c)
{
	char	**arr;
	size_t	words;
	size_t	i;
	size_t	start;
	size_t	k;

	if (s == NULL)
		return (NULL);
	words = count_words(s, c);
	arr = (char **)malloc(sizeof(char *) * (words + 1));
	if (arr == NULL)
		return (NULL);
	i = 0;
	k = 0;
	while (k < words)
	{
		while (s[i] == c)
			i++;
		start = i;
		while (s[i] && s[i] != c)
			i++;
		arr[k] = sbs_substr(s, (unsigned int)start, i - start);
		if (arr[k] == NULL)
			return (free_partial(arr, k), NULL);
		k++;
	}
	arr[k] = NULL;
	return (arr);
}
