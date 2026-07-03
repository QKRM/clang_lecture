#include "libsbs.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define BUF_SIZE 4096

/* 도전 3 예시 답안: 파일을 읽어 버퍼에 담고, sbs_strnstr로 단어를 모두 찾는다. */
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
	char	buf[BUF_SIZE];
	char	*word;
	char	*found;
	ssize_t	n;
	int		fd;
	size_t	pos;
	int		count;

	word = "is";
	fd = open("sample.txt", O_RDONLY);
	if (fd < 0)
	{
		printf("sample.txt를 열 수 없습니다\n");
		return (1);
	}
	n = read(fd, buf, BUF_SIZE - 1);
	close(fd);
	if (n < 0)
	{
		printf("읽기 실패\n");
		return (1);
	}
	buf[n] = '\0';
	pos = 0;
	count = 0;
	while (pos < (size_t)n)
	{
		found = sbs_strnstr(buf + pos, word, (size_t)n - pos);
		if (!found)
			break ;
		printf("인덱스 %zu에서 발견\n", (size_t)(found - buf));
		count++;
		pos = (size_t)(found - buf) + str_len(word);
	}
	if (count == 0)
		printf("\"%s\"를 찾지 못함\n", word);
	else
		printf("\"%s\"를 %d번 찾음\n", word, count);
	return (0);
}
