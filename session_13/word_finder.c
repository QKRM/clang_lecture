#include "libsbs.h"
#include <stdio.h>

/* 도전 1 예시 답안: sbs_strnstr을 반복 호출해 단어가 등장하는 모든 위치를 찾는다. */
static size_t	str_len(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	main(void)
{
	char	*text;
	char	*word;
	size_t	text_len;
	size_t	word_len;
	size_t	pos;
	char	*found;
	int		count;

	text = "this is a test, this is only a test";
	word = "is";
	text_len = str_len(text);
	word_len = str_len(word);
	pos = 0;
	count = 0;
	while (pos < text_len)
	{
		found = sbs_strnstr(text + pos, word, text_len - pos);
		if (!found)
			break ;
		printf("인덱스 %zu에서 발견\n", (size_t)(found - text));
		count++;
		pos = (size_t)(found - text) + word_len;
	}
	if (count == 0)
		printf("\"%s\"를 찾지 못함\n", word);
	else
		printf("\"%s\"를 %d번 찾음\n", word, count);
	return (0);
}
