#include "libsbs.h"
#include <stdio.h>

/* 도전 2 예시 답안: sbs_strrchr로 마지막 '/'와 '.'을 찾아 파일명/확장자를 분리한다. */
int	main(void)
{
	char	*path;
	char	*slash;
	char	*dot;
	char	*filename;

	path = "/home/user/report.final.txt";
	slash = sbs_strrchr(path, '/');
	if (slash)
		filename = slash + 1;
	else
		filename = path;
	dot = sbs_strrchr(filename, '.');
	if (dot)
		printf("파일명: %s, 확장자: %s\n", filename, dot + 1);
	else
		printf("파일명: %s, 확장자 없음\n", filename);
	return (0);
}
