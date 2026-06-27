#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include "libsbs.h"

/* sbs_putstr_fd 출력을 임시 파일로 받아 비교. NULL 입력도 테스트. */
int	main(int argc, char **argv)
{
	char	buf[64];
	int		fd;
	int		n;
	int		verbose;

	verbose = (argc > 1 && strcmp(argv[1], "-v") == 0);
	fd = open("/tmp/sbs_putstr_test.txt", O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (fd < 0)
	{
		printf("0/1\n");
		return (1);
	}
	sbs_putstr_fd("hello world", fd);
	sbs_putstr_fd(NULL, fd);
	sbs_putstr_fd("!", fd);
	close(fd);
	fd = open("/tmp/sbs_putstr_test.txt", O_RDONLY);
	n = read(fd, buf, 63);
	close(fd);
	if (n < 0)
		n = 0;
	buf[n] = '\0';
	if (strcmp(buf, "hello world!") == 0)
	{
		printf("1/1\n");
		return (0);
	}
	if (verbose)
		printf("  기대 \"hello world!\", 실제 \"%s\"\n", buf);
	printf("0/1\n");
	return (1);
}
