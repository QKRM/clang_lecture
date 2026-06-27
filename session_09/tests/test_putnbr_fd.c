#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include "libsbs.h"

/* sbs_putnbr_fd 출력을 비교. INT_MIN/INT_MAX/0/음수 포함. */
static int	check_one(int n, const char *expected, int verbose)
{
	char	buf[32];
	int		fd;
	int		len;

	fd = open("/tmp/sbs_putnbr_test.txt", O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (fd < 0)
		return (0);
	sbs_putnbr_fd(n, fd);
	close(fd);
	fd = open("/tmp/sbs_putnbr_test.txt", O_RDONLY);
	len = read(fd, buf, 31);
	close(fd);
	if (len < 0)
		len = 0;
	buf[len] = '\0';
	if (strcmp(buf, expected) == 0)
		return (1);
	if (verbose)
		printf("  n=%d: 기대 \"%s\", 실제 \"%s\"\n", n, expected, buf);
	return (0);
}

int	main(int argc, char **argv)
{
	int	pass;
	int	verbose;

	verbose = (argc > 1 && strcmp(argv[1], "-v") == 0);
	pass = 0;
	pass += check_one(0, "0", verbose);
	pass += check_one(42, "42", verbose);
	pass += check_one(-42, "-42", verbose);
	pass += check_one(123456, "123456", verbose);
	pass += check_one(2147483647, "2147483647", verbose);
	pass += check_one(-2147483648, "-2147483648", verbose);
	printf("%d/6\n", pass);
	return (pass != 6);
}
