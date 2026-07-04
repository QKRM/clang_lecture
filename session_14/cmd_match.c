#include "libsbs.h"
#include <stdio.h>

/* 도전 1 예시 답안: 입력이 어떤 명령어로 시작하는지 sbs_strncmp 프리픽스 비교로 판별한다. */
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
	char	*commands[] = {"help", "exit", "list", "load", NULL};
	char	*input;
	size_t	len;
	int		i;

	input = "list all files";
	i = 0;
	while (commands[i])
	{
		len = str_len(commands[i]);
		if (sbs_strncmp(input, commands[i], len) == 0
			&& (input[len] == ' ' || input[len] == '\0'))
		{
			printf("명령어 인식: %s\n", commands[i]);
			return (0);
		}
		i++;
	}
	printf("알 수 없는 명령어\n");
	return (0);
}
